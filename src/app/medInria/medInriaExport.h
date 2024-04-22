#pragma once
/*=========================================================================

 medInria

 Copyright (c) INRIA 2024. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#ifdef WIN32
    #ifdef medInria_EXPORTS
        #define MEDINRIA_EXPORT __declspec(dllexport)
    #else
        #define MEDINRIA_EXPORT __declspec(dllimport)
    #endif
#else
    #define MEDINRIA_EXPORT
#endif
