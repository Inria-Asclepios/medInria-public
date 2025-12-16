#ifndef ITKINRDATAIMAGEREADERPLUGINEXPORT_H
#define ITKINRDATAIMAGEREADERPLUGINEXPORT_H

#if defined(_WIN32)
    #ifdef itkINRDataImageReaderPlugin_EXPORTS
        #define ITKINRDATAIMAGEREADERPLUGIN_EXPORT __declspec(dllexport) 
    #else
        #define ITKINRDATAIMAGEREADERPLUGIN_EXPORT __declspec(dllimport) 
    #endif
#else
    #define ITKINRDATAIMAGEREADERPLUGIN_EXPORT __attribute__ ((visibility ("default")))
#endif

#endif
