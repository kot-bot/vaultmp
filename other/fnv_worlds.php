<?php

function import($file,$dlc)
{
	global $db;
	$f=file_get_contents($file);
	if($f===FALSE)
		die("Error loading $file");
	$c=explode("\n",$f);
	createTable("worldspaces");
	foreach($c as $t)
	{
		list($name,$id,$x,$y,$scale,$ox,$oy)=explode("|",$t);
		
		$id=hexdec($id);

if ($id == 0)
continue;
                $prep = $db->prepare("insert into worldspaces (baseID,x_width,y_width,scale,x_offset,y_offset,dlc) values (?, ?, ?, ?, ?, ?, ?)");
                if ($prep === FALSE) {
			echo "Fail: " . $id;
			continue;
		}
		$r = $prep->execute(array($id, $x, $y, $scale, $ox, $oy, $dlc));
if (!$r) {
$arr = $prep->errorInfo();
echo $arr[2];
}
	}
}


function createTable($tb)
{
	global $db;
	$db->exec("CREATE TABLE $tb (baseID integer(11),x_width integer(11),y_width integer(11),scale float(11),x_offset integer(11),y_offset integer(11),dlc integer(11))");
}

$db = new PDO('sqlite:newvegas.sqlite');
if(!$db)
{
    die("Errore Sqlite");
}

import("data/base_wrld_list.txt",0);
import("data/dm_wrld_list.txt",1);
import("data/hh_wrld_list.txt",2);
import("data/owb_wrld_list.txt",3);
import("data/lr_wrld_list.txt",4);