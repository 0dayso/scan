<?php

@$shell=$_GET["shell"];     //http://127.0.0.1:8888/webshell.php?shell=http://hongzecy.com/ar.php|long
$fp=fopen("123webshell.txt","a+"); 

fputs($fp,$shell); 

fputs($fp,"\r\n"); 

fclose($fp); 

echo "-------��¼�Ѿ�д��TXT �ɹ�<br/>"; 


?>
