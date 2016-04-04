/**
All code here adapted (modified as little as possible) from 
www.luckyspin.org
Adaptation by Gary Lewandowski, 14 October 2007.

Original header comments follow.
**/

/*
 * This is a very simple example of how to use libcurl from within 
 * a C++  program. The basic idea is that you want to retrieve the 
 * contents of a web page as a string. Obviously, you can replace 
 * the buffer object with anything you want and adjust elsewhere 
 * accordingly.
 * 
 * Hope you find it useful..
 * 
 * Todd Papaioannou 
 */


#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <curl/curl.h>
#include "SimpleCurl.h"
 #include "URLgraph.h"

using namespace std;

   int SimpleCurl::writer(char *data, size_t size, size_t nmemb,
                  std::string *buffer)
   {
  // What we will return
     int result = 0;

  // Is there anything in the buffer?
     if (buffer != NULL)
     {
    // Append the data to the buffer
       buffer->append(data, size * nmemb);

    // How much did we write?
       result = size * nmemb;
     }

     return result;
   }

   SimpleCurl::SimpleCurl(string url)
   {
	if (getURL(url) == -1) exit(-1);
   }
   bool not_url_char(char c){
     static const string url_ch = "~;/?:@=&$-_.+!*'(),";
     return !(isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
   }


   string::const_iterator url_end(string::const_iterator b, string::const_iterator e){
    return find_if(b, e, not_url_char);
   }

   string::const_iterator url_beg(string::const_iterator b, string::const_iterator e){
    static const string sep = "://";
    typedef string::const_iterator iter;
    iter i = b;
    while((i = search(i,e,sep.begin(), sep.end())) != e){
      if(i!=b && i + sep.size() != e){
        iter beg = i;
        while(beg != b && isalpha(beg[-1])){
          beg--;
        }
        if(beg !=i && !not_url_char(i[sep.size()])){
          return beg;
        }
      }
      i += sep.size();
    }
    return e;
   }

   int SimpleCurl::getURL(string url)
    {
	     buffer = "";
       // Create our curl handle
       curl = curl_easy_init();

       if (curl)
       {
         // Now set up all of the curl options
         curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
         curl_easy_setopt(curl, CURLOPT_HEADER, 0);
         curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,1);
         curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST,2); 
         curl_easy_setopt(curl,CURLOPT_CAINFO,"/MinGW/MSYS/1.0/local/bin/curl-ca-bundle.crt");

         // Attempt to retrieve the remote page
         result = curl_easy_perform(curl);

         // Always cleanup
         curl_easy_cleanup(curl);

         // Did we succeed?
         if (result != CURLE_OK)
         {
                cout << "Error: [" << result << "] - " << errorBuffer;
		            return 0;
         }
         return buffer.length();
       }
       return 0;
     }
  vector<string> SimpleCurl::find_urls(const string& s){
    vector<string> ret;
    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();
    while(b!=e){
      b = url_beg(b,e);
      if(b!=e){
        iter after = url_end(b,e);
        ret.push_back(string(b,after));
        b = after;
      }
    }
    return ret;
  }
  bool SimpleCurl::findTarget(const string& s,string target){
      if(s.find(target)!= string::npos){
        return true;
      }
      return false;
  }

  string SimpleCurl::getRetrievedDocument()
  { 
	return buffer;
  }

