#!/bin/bash
# Name: Pao Yu
# ID: yupao@uwindsor.ca
# Description: Assignment #01
# Synopsis: Backup files from current or target directory into a tar file.
# Test Usage Case 1: ./backup.sh txt bin c cpp py
# Test Usage Case 2: ./backup.sh -t ./test/ txt bin c cpp py

function display_script_information() {
	echo "---------------------------------------------------------------------------"
	echo " ./backup.sh -- Script Information"
	echo "---------------------------------------------------------------------------"
	echo " Backup files from current or target directory into a tar file."
	echo " Script usage: $(basename $0) [-t directory] suffix-1 [suffix-2] [suffix-x]"
	echo "---------------------------------------------------------------------------"
}

function main() {
	targetDirectoryIsActive=false
	display_script_information
	check_options $@
	make_backup_directory
	backup_suffixes $@
	create_tar_file
	remove_temporary_files
}

function make_backup_directory() {
	directoryName=`date | tr -d " :"`
	mkdir "$directoryName"
	echo "(1/4) Creating temporary backup directory \"$directoryName\"..."
}

function check_options() {

	while getopts 't:' OPTION; 
	do
		case "$OPTION" in
			t)	targetDirectoryIsActive=true
				targetDirectory="$OPTARG"
				
				if [ -d "$targetDirectory" ]; then 
					echo "Found target directory \"$targetDirectory\"";
					
					case "$targetDirectory" in
					*/) # targetDirectory has a trailing slash
						targetDirectory=${targetDirectory%/}
    					;;
					*)	# targetDirectory has no trailing slash
    					;;
					esac
				else 
					echo "Argument is not a directory. Backup operation aborted.";
					echo " "
     				exit 1
				fi
      			;;
  		esac
	done
	shift "$(($OPTIND - 1))"
	
}

function backup_suffixes() {

	if $targetDirectoryIsActive;
	then
		echo "(2/4) Copying target directory \"$targetDirectory\" files with suffix... "
		for suffix in "${@:3}"; 
		do 
			echo "Copying .$suffix files..."
			cp $targetDirectory/*.$suffix ./$directoryName/
		done
	else
		echo "(2/4) Copying current directory files with suffix..."
		for suffix in "$@"; 
		do
			echo "Copying .$suffix files..."
			cp *.$suffix ./$directoryName/
		done
	fi
		echo "File transfer to temporary directory complete."
}

function create_tar_file() {
	echo "(3/4) Creating backup .tar file..."
	if [ -f ./archive.tar ]; then
		echo "Overwriting existing archive.tar file..."
	fi
	tar -cvzf archive.tar $directoryName/
}

function remove_temporary_files() {
	echo "(4/4) Cleaning temporary backup files..."
	rm -rf $directoryName/
	echo "Backup process complete!"
	echo "Generated new file \"archive.tar\" in current directory."
	echo " "
}

main $@











