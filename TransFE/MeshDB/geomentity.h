/***************************************************************************
 *   Copyright (c) 2012 by Timothy C. Raymond                              *
 *   tc.raymond@ieee.org												   *
 *   All rights reserved.												   *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *      - Redistributions of source code must retain the above copyright   *
 *        notice, this list of conditions and the following disclaimer.    *
 *      - Redistributions in binary form must reproduce the above          *
 *        copyright notice, this list of conditions and the following      *
 *		  disclaimer in the documentation and/or other materials provided  *
 *		  with the distribution.                                           *
 *                                                                         *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  *
 *   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
 *   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN     *
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
 *   POSSIBILITY OF SUCH DAMAGE.                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef GEOMENTITY_H
#define GEOMENTITY_H

#include <map>
#include <string>

using namespace std;

//Attributes are currently restricted to numbers of type double
//Often times, as in the case of contraints, a value of 0 is meaningful
//When we want to indicate that the attribute does not exist ("a null attribute")
//we need to return a number that we can check for the hopefully is not used in real cases
#define NO_ATTRIB -999

class GeomEntity{
public:
   ///Default constructor
    GeomEntity();

   ///Default destructor
    ~GeomEntity();
   
   ///Retrieve an attribute
    double getAttribute(string key);
    
   ///Add an attribute designated by a string "key"
    void addAttribute(string key, double value);
    
   ///Clear all attributes associated with the instance
    void clearAttributes();

protected:
   ///This is a multimap to hold all of the attributes (key/value pairs)
   ///The multimap allows for quick (and brainless) retrieval of a value given
   ///a key string.  This could (and probably should) be a map.
   multimap<string, double> attributes;

};

#endif
