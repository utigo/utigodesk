{
    'targets': [
        {
            'target_name': 'utigodesk_addon',
            'cflags!': ['-fno-exceptions'],
            'cflags_cc!': ['-fno-exceptions'],
            'sources': [
                'src/cpp/utigodesk_addon.cc'
            ],
            'include_dirs': [
                "<!@(node -p \"require('node-addon-api').include\")",
                '../include'
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS', 'NDEBUG'],
            'msvs_configuration_attributes': {
                'CharacterSet': '1'
            },
            'msvs_settings': {
                'ClCompile': {
                    "LanguageStandard": "stdcpplatest"
                },
                'VCCLCompilerTool': {'ExceptionHandling': 0,
                                     'RuntimeLibrary': 2,
                                     'Optimization': 2
                                    },
                'VCLinkerTool': {
                    'LinkTimeCodeGeneration': 1,
                    'AdditionalLibraryDirectories': [
                        '../../lib/Release/x64'
                    ],
                    'AdditionalDependencies':[
                        'ws2_32.lib',
                        'win32utils.lib'
                    ]
                }
            }
        },
        {
            'target_name': 'utigodesk_callback',
            'cflags!': ['-fno-exceptions'],
            'cflags_cc!': ['-fno-exceptions'],
            'sources': [
                'src/cpp/utigodesk_callback.cc'
            ],
            'include_dirs': [
                "<!@(node -p \"require('node-addon-api').include\")",
                '../include'
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS', 'NDEBUG'],
            'msvs_configuration_attributes': {
                'CharacterSet': '1'
            },
            'msvs_settings': {
                'ClCompile': {
                    "LanguageStandard": "stdcpplatest"
                },
                'VCCLCompilerTool': {'ExceptionHandling': 0,
                                     'RuntimeLibrary': 2,
                                     'Optimization': 2
                                    },
                'VCLinkerTool': {
                    'LinkTimeCodeGeneration': 1,
                    'AdditionalLibraryDirectories': [
                        '../../lib/Release/x64'
                    ],
                    'AdditionalDependencies':[
                        'ws2_32.lib'
                    ]
                }
            }
        }
    ]
}
