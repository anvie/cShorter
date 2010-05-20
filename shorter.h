/*
 *  shorter.h
 *  shorter
 *
 *  Created by Robin Marufi on 5/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __SHORTER_H__
# define __SHORTER_H__


extern "C" {
	static PyObject *
	shorter_system(PyObject *self, PyObject *args);
	static PyObject*
	shorter_sort(PyObject *self, PyObject* args);
	static PyObject*
	shorter_rank(PyObject *self, PyObject* args);
	PyMODINIT_FUNC
	initshorter(void);
};




#endif // __SHORTER_H__

