################################################################################
#
# medInria
#
# Copyright (c) INRIA 2022. All rights reserved.
# See LICENSE.txt for details.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
################################################################################

function(set_external_resources target)

################################################################################
#
# Usage: set_external_resources(target [APPEND]
#                               [DESTINATION destination]
#                               [FILES [files...]]
#                               [DIRECTORIES [directories...]])
#
# Associates resources with a target. These resourcs either already exist or are
# generated by the target. This command only declares the resources and does not
# cause them to be imported at the build, install or packaging steps (see the
# 'import_external_resources' command for that). If the resources are destined
# to be imported in the same target that declares them, it is simpler to use the
# FILES or DIRECTORIES options of 'import_external_resource' directly).
# (this command populates the ${PROJECT_NAME}_RESOURCES property of the target)
#
# The options are:
#
# APPEND
#     With this option, the resources are added to the previous resources of the
#     target. Leaving the option out will drop the previously declared
#     resources.
#
# DESTINATION
#     Specify a subdirectory relative to the final import location.
#
# FILES, DIRECTORIES
#     Specify resource files or directories to add (the contents of the
#     directories will be copied to the destination folder).
#
################################################################################

    cmake_parse_arguments(PARSE_ARGV 1 "ARG"
        "APPEND"
        "DESTINATION"
        "FILES;DIRECTORIES"
        )

    if (NOT (ARG_FILES OR ARG_DIRECTORIES))
        message(FATAL_ERROR "No resources specified.")
    endif()

    if (ARG_DESTINATION)
        set(destination "${ARG_DESTINATION}")
    else()
        set(destination ".")
    endif()

    if (ARG_APPEND)
        set(append APPEND)
    else()
        set(append)
    endif()

    _build_resource_group(resources ${destination} FILES ${ARG_FILES} DIRECTORIES ${ARG_DIRECTORIES})
    set_property(TARGET ${target} ${append} PROPERTY ${PROJECT_NAME}_RESOURCES ${resources})

endfunction()

################################################################################
# Internal
################################################################################

macro(_build_resource_group resources_var destination)

    cmake_parse_arguments("ARG"
        ""
        ""
        "FILES;DIRECTORIES"
        ${ARGN}
        )

    set(${resources_var} ${destination} _FILES_ ${ARG_FILES} _DIRECTORIES_ ${ARG_DIRECTORIES} _END_GROUP_)

endmacro()
