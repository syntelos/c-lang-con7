#!/bin/bash
#
function usage {
    cat<<EOF
Synopsis

  $0 init

Description

  Initialize a recursive chain of submodues.

Synopsis

  $0 list

Description

  List a recursive chain of submodues.

EOF
    exit 1
}
function list {

    git submodule status --recursive | awk '{print $2}'
}
function submodule {

    if r=$(git submodule status | awk '{print $2}') && [ -n "${r}" ]
    then
        echo "${r}"

        return 0
    else
        return 1
    fi
}

if [ "${1}" ]
then
    case "${1}" in

        list)
            if list
            then
                exit 0
            else
                exit 1
            fi
            ;;

        init)

            while dir=$(submodule) && cd ${dir}
            do
                git submodule update --init
            done
            exit 0
            ;;
        *)
            usage
            ;;
    esac
else
    usage
fi
