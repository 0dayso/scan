<?php
//=================================
$conn = @mysql_connect('localhost:3306','root','316118740') or die("�������ݿ����!!!");  //�������ݿ�
mysql_select_db('hhmm',$conn) or die("�����ݴ���!!!");  //������
mysql_query("set names 'GBK'"); //ʹ��GBK���ı���;

//=================================
?>
