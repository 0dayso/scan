<?php
//=================================
$conn = @mysql_connect('localhost:3306', 'root', '316118740') or die("�������ݿ����!!!");  //�������ݿ�
mysql_select_db('999kankan',$conn) or die("�����ݴ���!!!");  //������
//mysql_query("SET NAMES UTF8");
//mysql_query("set character_set_client=utf8"); 
//mysql_query("set character_set_results=utf8");
mysql_query("set names 'GBK'"); //ʹ��GBK���ı���;

//=================================
?>
