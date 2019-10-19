/* **************************************************************************
 * @version $Id: cppcompat.h,v 0.0 2006/06/01 01:11:00 legolas558 Exp $
 *
 * File:		cppcompat.h
 * Content:		include file for some missing C standard definitions
 * Notes:		shared between my various projects, provides bool and inline
 *
 * Copyright(c) 2006 by legolas558
 *
 * **************************************************************************/

#ifndef	__CPPCOMPAT_H
#define __CPPCOMPAT_H

#ifndef bool
	#define	bool	unsigned int
	#define	true	1
	#define	false	0
#endif

#ifdef	inline
#define	L_INLINE	inline
#endif

#ifndef	L_INLINE
#ifdef	_inline
#define	L_INLINE	_inline
#endif
#endif

#ifndef	L_INLINE
#ifdef	__inline
#define	L_INLINE	__inline
#endif
#endif

#ifndef	L_INLINE
#define	L_INLINE
#endif


#endif
