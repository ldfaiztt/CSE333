/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

#include "./FileReader.h"
#include "./HttpConnection.h"
#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpServer.h"
#include "./libhw3/QueryProcessor.h"

using std::cerr;
using std::cout;
using std::endl;

namespace hw4 {

// This is the function that threads are dispatched into
// in order to process new client connections.
void HttpServer_ThrFn(ThreadPool::Task *t);

// Given a request, produce a response.
HttpResponse ProcessRequest(const HttpRequest &req,
                            const std::string &basedir,
                            const std::list<std::string> *indices);

// Process a file request.
HttpResponse ProcessFileRequest(const std::string &uri,
                                const std::string &basedir);

// Process a query request.
HttpResponse ProcessQueryRequest(const std::string &uri,
                                 const std::list<std::string> *indices);

bool HttpServer::Run(void) {
  // Create the server listening socket.
  int listen_fd;
  cout << "  creating and binding the listening socket..." << endl;
  if (!ss_.BindAndListen(AF_UNSPEC, &listen_fd)) {
    cerr << endl << "Couldn't bind to the listening socket." << endl;
    return false;
  }

  // Spin, accepting connections and dispatching them.  Use a
  // threadpool to dispatch connections into their own thread.
  cout << "  accepting connections..." << endl << endl;
  ThreadPool tp(kNumThreads);
  while (1) {
    HttpServerTask *hst = new HttpServerTask(HttpServer_ThrFn);
    hst->basedir = staticfile_dirpath_;
    hst->indices = &indices_;
    if (!ss_.Accept(&hst->client_fd,
                    &hst->caddr,
                    &hst->cport,
                    &hst->cdns,
                    &hst->saddr,
                    &hst->sdns)) {
      // The accept failed for some reason, so quit out of the server.
      break;
    }
    // The accept succeeded; dispatch it.
    tp.Dispatch(hst);
  }
  return true;
}

void HttpServer_ThrFn(ThreadPool::Task *t) {
  // Cast back our HttpServerTask structure with all of our new
  // client's information in it.
  std::unique_ptr<HttpServerTask> hst(static_cast<HttpServerTask *>(t));
  cout << "  client " << hst->cdns << ":" << hst->cport << " "
       << "(IP address " << hst->caddr << ")" << " connected." << endl;

  bool done = false;
  HttpConnection hc(hst->client_fd);
  while (!done) {
    // Use the HttpConnection class to read in the next request from
    // this client, process it by invoking ProcessRequest(), and then
    // use the HttpConnection class to write the response.  If the
    // client sent a "Connection: close\r\n" header, then shut down
    // the connection.

    // MISSING:

    // get the next request
    HttpRequest req;
    if (!hc.GetNextRequest(&req)) {
      close(hst->client_fd);
      done = true;
    }

    // process the request
    HttpResponse rep = ProcessRequest(req, hst->basedir, hst->indices);

    // write the response
    if (!hc.WriteResponse(rep)) {
      close(hst->client_fd);
      done = true;
    }

    // close the connection if the client sent "Connection: close\r\n"
    if (req.headers["connection"] == "close") {
      close(hst->client_fd);
      done = true;
    }
  }
}

HttpResponse ProcessRequest(const HttpRequest &req,
                            const std::string &basedir,
                            const std::list<std::string> *indices) {
  // Is the user asking for a static file?
  if (req.URI.substr(0, 8) == "/static/") {
    return ProcessFileRequest(req.URI, basedir);
  }

  // The use must be asking for a query.
  return ProcessQueryRequest(req.URI, indices);
}


HttpResponse ProcessFileRequest(const std::string &uri,
                                const std::string &basedir) {
  // The response we'll build up.
  HttpResponse ret;

  // Steps to follow:
  //  - use the URLParser class to figure out what filename
  //    the user is asking for.
  //
  //  - use the FileReader class to read the file into memory
  //
  //  - copy the file content into the ret.body
  //
  //  - depending on the file name suffix, set the response
  //    Content-type header as appropriate, e.g.,:
  //      --> for ".html" or ".htm", set to "text/html"
  //      --> for ".jpeg" or ".jpg", set to "image/jpeg"
  //      --> for ".png", set to "image/png"
  //      etc.
  //
  // be sure to set the response code, protocol, and message
  // in the HttpResponse as well.
  std::string fname = "";

  // MISSING:

  // parse uri to get file name
  URLParser p;
  p.Parse(uri);
  fname += p.get_path();

  // get rid of /static/ in file name
  fname = fname.replace(0, 8, "");
  FileReader fr(basedir, fname);

  if (fr.ReadFile(&ret.body)) {
    // get the file name suffix
    size_t dot_pos = fname.rfind(".");
    std::string suffix = fname.substr(dot_pos, fname.length() - 1);

    // set Content-type header based on file name suffix
    if (suffix == ".html" || suffix == ".htm")
      ret.headers["Content-type"] = "text/html";
    else if (suffix == ".csv")
      ret.headers["Content-type"] = "text/csv";
    else if (suffix == ".css")
      ret.headers["Content-type"] = "text/css";
    else if (suffix == ".js")
      ret.headers["Content-type"] = "text/javascript";
    else if (suffix == ".txt" || suffix == ".")
      ret.headers["Content-type"] = "text/plain";
    else if (suffix == ".xml")
      ret.headers["Content-type"] = "text/xml";
    else if (suffix == ".jpg" || suffix == ".jpeg")
      ret.headers["Content-type"] = "image/jpeg";
    else if (suffix == ".gif")
      ret.headers["Content-type"] = "image/gif";
    else if (suffix == ".png")
      ret.headers["Content-type"] = "image/png";
    else if (suffix == ".tiff")
      ret.headers["Content-type"] = "image/tiff";
    else
      ret.headers["Content-type"] = "application/octet-stream";

    // set the response protocol, response code, and message
    ret.protocol = "HTTP/1.1";
    ret.response_code = 200;
    ret.message = "OK";
    return ret;
  }

  // If you couldn't find the file, return an HTTP 404 error.
  ret.protocol = "HTTP/1.1";
  ret.response_code = 404;
  ret.message = "Not Found";
  ret.body = "<html><body>Couldn't find file \"";
  ret.body +=  EscapeHTML(fname);
  ret.body += "\"</body></html>";
  return ret;
}

HttpResponse ProcessQueryRequest(const std::string &uri,
                                 const std::list<std::string> *indices) {
  // The response we're building up.
  HttpResponse ret;

  // Your job here is to figure out how to present the user with
  // the same query interface as our solution_binaries/http333d server.
  // A couple of notes:
  //
  //  - no matter what, you need to present the 333gle logo and the
  //    search box/button
  //
  //  - if the user had previously typed in a search query, you also
  //    need to display the search results.
  //
  //  - you'll want to use the URLParser to parse the uri and extract
  //    search terms from a typed-in search query.  convert them
  //    to lower case.
  //
  //  - you'll want to create and use a hw3::QueryProcessor to process
  //    the query against the search indices
  //
  //  - in your generated search results, see if you can figure out
  //    how to hyperlink results to the file contents, like we did
  //    in our solution_binaries/http333d.

  // MISSING:

  // 333gle logo and search box/button
  ret.body = "<html><head><title>333gle</title></head>\r\n";
  ret.body += "<body>\r\n";
  ret.body += "<center style=\"font-size:500%;\">\r\n";
  ret.body += "<span style=\"position:relative;bottom:-0.33em;";
  ret.body += "color:orange;\">3</span>";
  ret.body += "<span style=\"color:red;\">3</span>";
  ret.body += "<span style=\"color:gold;\">3</span>";
  ret.body += "<span style=\"color:blue;\">g</span>";
  ret.body += "<span style=\"color:green;\">l</span>";
  ret.body += "<span style=\"color:red;\">e</span>\r\n";
  ret.body += "</center>\r\n";
  ret.body += "<p>\r\n";
  ret.body += "<div style=\"height:20px;\"></div>\r\n";
  ret.body += "<center>\r\n";
  ret.body += "<form action=\"/query\" method=\"get\">\r\n";
  ret.body += "<input type=\"text\" size=30 name=\"terms\" />\r\n";
  ret.body += "<input type=\"submit\" value=\"Search\" />\r\n";
  ret.body += "</form>\r\n";
  ret.body += "</center><p>\r\n";

  // parse the uri to get query and convert the query to lower case
  URLParser p;
  p.Parse(uri);
  std::string query = p.get_args()["terms"];
  boost::trim(query);
  boost::to_lower(query);

  // display the rearch results if the user typed in search query
  if (uri.find("query?terms=") != std::string::npos) {
    // split the query string into query words
    std::vector<std::string> qvec;
    boost::split(qvec, query, boost::is_any_of(" "), boost::token_compress_on);

    // construct a QueryProcessor to answer query
    hw3::QueryProcessor qp(*indices, false);

    // search for the matched documents
    std::vector<hw3::QueryProcessor::QueryResult> qr = qp.ProcessQuery(qvec);

    if (qr.size() == 0) {
      // no matched documents found
      ret.body += "<p><br>\r\n";
      ret.body += "No results found for <b>";
      ret.body += EscapeHTML(query);
      ret.body += "</b>\r\n";
      ret.body += "<p>\r\n";
      ret.body += "\r\n";
    } else {
      // display the number of results found
      std::stringstream ss;
      ret.body += "<p><br>\r\n";
      ss << qr.size();
      ret.body += ss.str();
      ss.str("");
      ret.body += (qr.size() == 1) ? " result " : " results ";
      ret.body += "found for <b>";
      ret.body += EscapeHTML(query);
      ret.body += "</b>\r\n";
      ret.body += "<p>\r\n\r\n";

      // display each matched document with hyperlink
      ret.body += "<ul>\r\n";
      for (uint32_t i = 0; i < qr.size(); i++) {
        ret.body += " <li> <a href=\"";
        if (qr[i].document_name.substr(0, 7) != "http://")
          ret.body += "/static/";
        ret.body += qr[i].document_name;
        ret.body += "\">";
        ret.body += EscapeHTML(qr[i].document_name);
        ret.body += "</a>";
        ret.body += " [";
        ss << qr[i].rank;
        ret.body += ss.str();
        ss.str("");
        ret.body += "]<br>\r\n";
      }
      ret.body += "</ul>\r\n";
    }
  }

  // the end of the response body
  ret.body += "</body>\r\n";
  ret.body += "</html>\r\n";

  // set the response protocol, response code, and message
  ret.protocol = "HTTP/1.1";
  ret.response_code = 200;
  ret.message = "OK";
  return ret;
}

}  // namespace hw4
