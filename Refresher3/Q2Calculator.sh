#! /bin/bash

function add()
{
	ans=0
	for (( i = 1; i < ${#a[@]}; i++ )); do
		ans=`expr $ans + ${a[i]}`
	done
	echo $ans
}

function sub()
{
	ans=${a[1]}
	for (( i = 2; i < ${#a[@]}; i++ )); do
		ans=`expr $ans - ${a[i]}`
	done
	echo $ans
}

function mul()
{
	ans=1
	for (( i = 1; i < ${#a[@]}; i++ )); do
		ans=`expr $ans \* ${a[i]}`
	done
	echo $ans
}

function div()
{
	ans=${a[1]}
	for (( i = 2; i < ${#a[@]}; i++ )); do
		ans=`expr $ans / ${a[i]}`
	done
	echo $ans
}

function exp()
{
	ans=${a[1]}
	for (( i = 2; i < ${#a[@]}; i++ )); do
		ans=$(echo $(( ans ** ${a[i]} )))
	done
	echo $ans
}

a=("$@")

case $1 in
	"add" ) add
		;;
	"sub" ) sub
		;;
	"mul" ) mul
		;;
	"div" ) div
		;;
	"exp" ) exp
		;;
esac