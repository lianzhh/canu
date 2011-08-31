/**************************************************************************
 * This file is part of Celera Assembler, a software program that
 * assembles whole-genome shotgun reads into contigs and scaffolds.
 * Copyright (C) 2005, J. Craig Venter Institute. All rights reserved.
 * Author: Brian Walenz
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received (LICENSE.txt) a copy of the GNU General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *************************************************************************/

#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H

static const char* rcsid_IOEXCEPTION_H = "$Id: IOException.h,v 1.2 2011-08-31 06:49:27 mkotelbajcvi Exp $";

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

#include "ExceptionUtils.h"
#include "RuntimeException.h"
#include "StringUtils.h"

class IOException : public RuntimeException
{
public:
	IOException(const char* message = NULL, RuntimeException* cause = NULL) throw();
	IOException(string message = string(), RuntimeException* cause = NULL) throw();
	
protected:
	virtual void initialize() throw();
};

#endif