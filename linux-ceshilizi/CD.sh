#!/bin/bash

menu_choice=""
current_cd=""
title_file="title.cdb"
tracks_file="tracks.cdb"
temp_file=/tmp/cdb.$$
trap 'rm -f $temp_file' EXIT

get_return(){
echo -e "press return \c"
read x
return 0
}

get confirm(){
echo -e "are you sure? \c"
while true
do 
read x
case "$x" in
y|yes|Y|Yes|YES)
return 0;;
n|no|N|No|NO)
echo
echo "cancelled"
return 1;;
*) echo "please enter yes or no";;
esac
done 
}

set_menu_choice(){
clear
echo "options:-"
echo
echo "a) add new CD"
echo "f) find CD"
echo "c) count the CDs and tracks in the catalog"
if["$cdcatnum" != ""]; then
echo "1) list tracks on $cdtitle"
echo "r) remove $cdtitle"
echo "u) update track information for $cdtitle"
fi
echo "q) quit"
echo -e "please enter choice then press return \c"
read menu_choice
return  
}

insert_title(){
echo $* >> $title_file
return 
}

insert_track(){
echo $* >> $tracks_file
return 
}

add_record_tracks(){
echo "enter track information for this CD"
echo "when no more tracks enter q"
cdtrack=1
cdttitle=""
while["$cdttitle" != "q"]
do
echo -e "track $cdtrack,track title? \c"
read tmp
cdttitle=${tmp%%,*}
if["$tmp" != "$cdttitle"]; then
echo "sorry,no commas allowed"
continue
fi
if[-n "$cdttitle"]; then
if["$cdttitle" != "q"]; then
insert_track $cdcatnum,$cdtrack,$cdttitle
fi
else
cdttrack=$((cdtrack-1))
fi
cdtrack=$((cdtrack+1))
done
}

add_records(){
echo -e "enter catalog name \c"
read tmp
cdcatnum=${tmp%%,*}

echo -e "enter title \c"
read tmp
cdtitle=${tmp%%，*}

echo -e "enter type \c"
read tmp
cdtype=${tmp%%,*}

echo -e "enter artist/composer \c"
read tmp
cdac=${tmp%%.*}

echo about to add new entry
echo "$cdcatnum $cdtitle $cdtype &dac"

if get_confirm; then
insert_title $cdcatnum,$cdtitle,$cdtype,$cdac
add_record_tracks
else
remove_records
fi

return 
}

find_cd(){
if["$1" = "n"]; then
asklist=n
else
asklist=y
fi
cdcatnum=""
echo -e "enter a string to search for in the CD titles \c"
read searchstr
if["$searchstr" = ""]; then
return 0
fi 

grep "$searchstr" $title_file > $temp_file

set $(wc -l $temp_file)
linesfound=$1

case "linesfound" in
0) echo "sorry,nothing found"
   get return
   return 0
   ;;
1) ;;
2) echo "sorry,not unique."
   echo "found the following"
   cat $temp_file
   get_return
   return 0
esac

IFS=","
read cdcatnum cdtitle cdtype cdac < $temp_file
IFS=" "

if[-z "$cdcatnum"]; then
echo "sorry,could not extract catalog field from $temp_file"
get_return
return 0
fi

echo
echo catalog number: $cdcatnum
echo title: $cdtitle
echo type: $cdtype
echo artist/composer: $cdac
echo
get_return 

if["$asklist" = "y"]; then
echo -e "view tracks for this CD? \c"
read x
if["$x" = "y"]; then 
echo 
list_tracks
echo
fi 
fireturn 1
}

update_cd(){
if[-z "$cdcatnum"]; then
echo "you must select a CD first"
find_cd n 
fi
if[-n "$cdcanum"]; then
echo "current tracks are:-"
list-tracks
echo
echo "this will re-enter the tracks for $cdtitle"
get_confirm && {
grep -v "^$(cdcatnum)," $tracks_file > $temp_file
mv $temp_file $tracks_file
echo 
add_record_tracks
}
fi 
return 
}

count_cds(){
set $(wc -l $title_file)
num_titles=$1
set $(wc -l $tracks_file)
num_tracks=$1
echo found $num_titles CDs, with a total of $num_tracks tracks
get_return 
return 
}

remove_records(){
if[-z "cdcatnum"]; then 
echo you must select a CD first
find_cd n 
fi
if[-n "$cdcainum"]; then
echo "you are about to delete $cdtitle"
get_confirm && {
grep -v "^${cdcatnum}," $title_file > $temp_file
mv $temp_file $title_file
grep -v "^${cdcatnum}," $tracks_file > $temp_file
mv $temp_file $tracks_file
cacatnum=""
echo entry removed
}
get_return 
fi
return 
} 

list_tracks(){
if["$cdcatnum" = ""]; then
echo no CD selected yet
return
else
grep "^${cdcatnum}," $tracks_file > $temp_file
num_tracks=$(wc -l $temp_file)
if["$num_tracks" = "0"]; then
echo no tracks found for $detitle
else{
echo
echo "$cdtitle:-"
echo
cut -f 2- -d, $temp_file
echo
} | ${pager:-more}
fi
fi
get_return
return
}

rm -f $temp_file
if[! -f $ctitle_file]; then
touch $ctitle_file
fi 
if[! -f $tracks_file]; then
touch $track_file
fi

clesr
echo
echo
echo "Mini CD manager"
sleep 1

quit=n 
while["$quit" != "y"]
do
set_menu_choice
case "$menu_choice" in
a) add_records;;
r) remove_records;;
f) find_cd;;
u) update_cd;;
c) count_cds;
l) list_tracks;;
b)
echo 
more $title_file
echo 
get_return
q | Q) quit=y;;
*) echo "sorry, choice not recongnized";;
esac
done

rm -f $temp_file
echo "finished"
exit 0  