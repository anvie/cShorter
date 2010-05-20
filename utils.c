/*
 *  utils.c
 *  shorter
 *
 *  Created by Robin Marufi on 5/21/10.
 *  Copyright 2010 Anlab Software. All rights reserved.
 *
 */

#include "utils.h"
#include <string.h>

char* to_lower(char* buff){
	
	int cnt = strlen(buff);
	int i;
	for (i=0; i<cnt;++i) {
		buff[i] = tolower(buff[i]);
	}
	return buff;
	
}



