#!/bin/bash

for X in `ls *.*` ; do
	for Y in `ls *.*` ; do
		for Z in `ls *.*` ; do
			echo "($X;$Y;$Z)" ; done ; done ; done 
