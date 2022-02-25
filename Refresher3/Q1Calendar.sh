#! /bin/bash

d=${1:0:2}
m=${1:3:2}
y=${1:6:4}
case $m in
    "01") 
        if [[ $d -gt 31 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "02") 
        if [[ $(expr $y % 100) == 0 ]] && [[ $(expr $y % 400) != 0 ]] && [[ $d -gt 28 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        elif [[ $(expr $y % 4) != 0 ]] && [[ $d -gt 28 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        elif [[ $(expr $y % 4) == 0 ]] && [[ $d -gt 29 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "03") 
        if [[ $d -gt 31 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "04") 
        if [[ $d -gt 30 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "05") 
        if [[ $d -gt 31 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "06") 
        if [[ $d -gt 30 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "07") 
        if [[ $d -gt 31 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "08") 
        if [[ $d -gt 31 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "09") 
        if [[ $d -gt 30 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "10") 
        if [[ $d -gt 31 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "11") 
        if [[ $d -gt 30 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
    "12") 
        if [[ $d -gt 31 ]] || [[ $d -lt 1 ]]; then
            echo "Invalid Date!"
            exit 1
        fi
        ;;
esac

cal $m $y