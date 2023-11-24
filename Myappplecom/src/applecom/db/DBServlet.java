package applecom.db;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.junit.Test;

public class DBServlet {
	public Connection getConne(){
         //DriverManager:注册驱动     创建连接
     	 //Connection : 表示与数据库创建的连接     一个连接
         //Statement : 操作数据库sql语句的对象    操作sql语句，并返回相应结果集的对象
         //ResultSet : 结果集或者一张虚拟表
         
             //注册驱动
             try {
                 Class.forName("com.mysql.jdbc.Driver");
                 System.out.println("1.成功进入Driver----");
             } catch (ClassNotFoundException e) {
                 // TODO Auto-generated catch block
                 System.out.println("error Driver");
                 
                 e.printStackTrace();
                 return null;
             }
            //获取连接Connection
         try {
             Connection conn = DriverManager.getConnection("jdbc:mysql://81.70.58.118:3306/applecom?serverTimezone=UTC&characterEncoding=utf8&amp", "root", "wSY0316@");
             System.out.println("2.成功与数据库进行连接Connection------");
             /*Statement stmt=conn.createStatement();
                ResultSet rs=stmt.executeQuery("select * from users");
                while(rs.next())
                {
                    System.out.println(rs.getString("surname"));
                }*/
             return conn;
         } catch (SQLException e) {
             // TODO Auto-generated catch block
             System.out.println("error Connection");
             e.printStackTrace();
             return null;
         }
     }
 
 }