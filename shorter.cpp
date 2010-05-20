/*
 *  shorter.c
 *  shorter
 *
 *  Created by Robin Marufi on 5/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <Python/Python.h>
#include "shorter.h"
#include "utils.h"

#include <iostream>
#include <string>

using namespace std;


static PyObject *SpamError;



static PyObject *
shorter_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;
	
    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return Py_BuildValue("i", sts);
}

static PyObject*
shorter_sort(PyObject *self, PyObject* args)
{
	PyObject* item1;
	PyObject* item2;
	
	if( !PyArg_ParseTuple(args, "OO", &item1, &item2) )
		return NULL;

	//PyObject_Print(item1, stdout, 0);
	
	int rv = 0;
	int val1; int val2;
	PyObject* attr_name =  Py_BuildValue("s","value");
	
	val1 = PyInt_AsLong( PyObject_GetAttr(item1,attr_name) );
	val2 = PyInt_AsLong( PyObject_GetAttr(item2,attr_name) );

	if (val1>val2) {
		rv = -1;
	}else if (val1<val2) {
		rv = 1;
	}else{
		val1 = PyInt_AsLong( PyObject_GetAttr(item1, Py_BuildValue("s","value2")) );
		val2 = PyInt_AsLong( PyObject_GetAttr(item1, Py_BuildValue("s","value2")) );
		if (val1>val2) {
			rv = -1;
		}else if (val1<val2) {
			rv = 1;
		}
	}
	
	//printf("item1: %d, item2: %d. rv: %d\n",item1,item2,rv);
	
	return Py_BuildValue("i",rv);
}


////////
#include <list>

list<string> split(string text,char sep)
{
	list<string> rv; 
	string::iterator it;
	int rng = 0;
	int pos = 0;
	for (it=text.begin(); it!=text.end(); it++) {
		if (*it==' ') {
			//printf("pos: %d, rng: %d\n",pos,rng);
			rv.push_back(text.substr(pos,rng));
			pos+=(rng+1);
			rng=0;
			continue;
		}
		rng++;
	}
	if (rng>0) {
		rv.push_back(text.substr(pos,rng));
		//printf("pos: %d, rng: %d. last push: %s\n",pos,rng,text.substr(pos,rng).c_str());
	}
	return rv;
}

string strip_unwanted_char(string text)
{
	string rv;
	string::iterator it;
	int pos = 0;
	int rng = 0;
	for (it=text.begin(); it!=text.end(); ++it) {
		if (*it > 48 && *it < 122) {
			rng++;
			continue;
		}

		if (*it < 48 || *it > 122) {
			//printf("pos: %d, rng: %d\n", pos, rng);
			rv += text.substr(pos,rng) + " ";
			pos += rng;
			pos++;
			rng = 0;
		}
		
	}
	if (rng>0) {
		rv += text.substr(pos,rng);
	}
	
	if (*rv.end() == ' ') {
		rv.end()[0] == 0x00;
	}
	
	//cout << rv.c_str() << endl;
	return rv;
}

template <class T>
bool list_contain(T& item,list<T> l)
{
	typename std::list<T>::iterator it;
	for (it=l.begin(); it!=l.end(); ++it) {
		if (*it == item) {
			return true;
		}
	}
	return false;
}

////////

static PyObject*
shorter_rank(PyObject *self, PyObject* args)
{
	PyObject* obj;
	char* keywords;
	int absrank;
	int rank = 0;
	
	if( !PyArg_ParseTuple(args, "Osi", &obj, &keywords, &absrank) )
		return NULL;
	
	PyObject* tmp = PyObject_GetAttrString(obj, "title");
	
	char* title = PyString_AsString(tmp);
	title = to_lower(title);
	keywords = to_lower(keywords);
	
	//printf("processing: %s\n", title);
	//printf("title: %s\nkeywords: %s\nabsrank: %d\n", title, keywords, absrank);
	
	// perfect match!
	if (strcmp(title, keywords) == 0) {
		rank = 2;
	}
	
	string stdkeywords = strip_unwanted_char(keywords);
	string stdtitle = strip_unwanted_char(title);
	
	//cout << "stdkeywrods: " << stdkeywords.c_str() << endl;
	//cout << "stdtitle: " << stdtitle.c_str() << endl; 
	
	//cout << "splitting keywords `" << stdkeywords.c_str() << "`...\n";
	list<string> splited_keywords = split(stdkeywords,' ');
	list<string>::iterator it;

	for (it=splited_keywords.begin(); it!=splited_keywords.end(); it++) {
		//cout << "keyw: " << *it << endl;
		
		if ( stdtitle.find(*it,0) != string::npos ) {
			rank += 1;
		}
	}
	
	// nilai spesial buat title pertama
	//list<string> splited_title = split(title, ' ');
	if (stdtitle.find(*splited_keywords.begin()) != string::npos) {
		rank += 2;
	}
	
	// pencarian tersambung
	if (splited_keywords.size() > 1) {
		if (stdtitle.find(*splited_keywords.begin() + " " + *(++splited_keywords.begin())) != string::npos) {
			rank += 2;
		}
	}
	
	return Py_BuildValue("i", rank);
}

static PyMethodDef ShorterMethods[] = {
	
    {"system", shorter_system, METH_VARARGS, "Execute a shell command."},
	{"sort", shorter_sort,  METH_VARARGS, "Sort a list faster"},
	{"rank", shorter_rank,  METH_VARARGS, "Rank a DocList faster"},
    
    {NULL, NULL, 0, NULL}        /* Sentinel */
};



PyMODINIT_FUNC
initshorter(void)
{
    PyObject *m;
	
    m = Py_InitModule("shorter", ShorterMethods);
    if (m == NULL)
        return;
	
    SpamError = PyErr_NewException((char*)"shorter.error", NULL, NULL);
    Py_INCREF(SpamError);
    PyModule_AddObject(m, "error", SpamError);
}





