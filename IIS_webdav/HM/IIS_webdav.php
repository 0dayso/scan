<?php  //�������
include("conn.php");
$psotip=$_SERVER["REMOTE_ADDR"];   #��ȡ�ύ��������IP
$tim=date('Y-m-d H:i:s',time());
//http://xxxx.com/IIS_webdav.php?URL=aaaaa
$sql="insert into IIS_webdav (url,postIP,time) VALUES ('$_REQUEST[URL]','$psotip','$tim')";
//print $sql;
mysql_query($sql)or die("������ݴ���!!!11122222222");
print "������ݳɹ�����222";
?>


