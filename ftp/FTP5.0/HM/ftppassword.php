<?php  //�������
include("conn.php");
//$_REQUEST["IP"]; //����
//$_REQUEST["user"]; //�û���
//$_REQUEST["password"]; //����
$ftproot=$_REQUEST["root"]; //Ȩ��
$tim=date('Y-m-d H:i:s',time());
//http://999kankan.com/ftppassword.php?IP=www.baidu.com&user=1111&password=2222&root=2

if ($ftproot==2)
{
$sql="insert into ftppassword2(IP,user,password,root,time) VALUES('$_REQUEST[IP]','$_REQUEST[user]','$_REQUEST[password]','2','$tim')";
//print $sql;
mysql_query($sql)or die("������ݴ���!!!11122222222");
print "������ݳɹ�����222";
}

if ($ftproot==3)
{
$sql="insert into ftppassword3(IP,user,password,root,time) VALUES('$_REQUEST[IP]','$_REQUEST[user]','$_REQUEST[password]','3','$tim')";
//print $sql;
mysql_query($sql)or die("������ݴ���!!!33333333");
print "������ݳɹ�����333";
}
//print $sql;
?>


