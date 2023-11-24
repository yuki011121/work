package winPack;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.SimpleDateFormat;

public class WinDAO {

	//声明Connection对象
    private Connection con;
    //驱动程序名
    String driver = "com.mysql.cj.jdbc.Driver";
    //URL指向要访问的数据库名mydata
    String url = "jdbc:mysql://localhost:3306/connectDB?useUnicode=true&amp&useSSL=false&amp&characterEncoding=UTF-8&amp&serverTimezone=GMT%2B8";
    //MySQL配置时的用户名
    private String user = "root";
    //MySQL配置时的密码
    private String password = "Zng19971018";
    //遍历查询结果集
	
	public void delete(int uid, int rid)
	{
		try {
	        //加载驱动程序
	        Class.forName(driver);
	        //1.getConnection()方法，连接MySQL数据库！！
	        con = DriverManager.getConnection(url,user,password);
	        //2.创建statement类对象，用来执行SQL语句！！
	        Statement statement = con.createStatement();
	        //要执行的SQL语句
	        String sql = "delete from win where uid="+ uid + "rid =" + rid + ';'; 
	        	//+ "and nums=" + nums + "and llevel=" + llevel +";"; 
	        //3.ResultSet类，用来存放获取的结果集！！
	        statement.execute(sql);
	        con.close();
	    } catch(ClassNotFoundException e) {   
	        //数据库驱动类异常处理
	        System.out.println("Sorry,can`t find the Driver!");   
	        e.printStackTrace();   
	        } catch(SQLException e) {
	        //数据库连接失败异常处理
	        e.printStackTrace();  
	        }catch (Exception e) {
	        // TODO: handle exception
	        e.printStackTrace();
	    }finally{
	        System.out.println("数据库数据成功获取！！");
	    }
	}

	public String insert(int uid, int rid, String win_time)
	{
		String rstr = "";
		try {
	        //加载驱动程序
	        Class.forName(driver);
	        //1.getConnection()方法，连接MySQL数据库！！
	        con = DriverManager.getConnection(url,user,password);
	        //2.创建statement类对象，用来执行SQL语句！！
	        Statement statement = con.createStatement();
	        //要执行的SQL语句
	        String sql = "insert into win (uid, rid, win_time) values ("
	        		+ uid + ',' + rid + ",\"" + win_time + "\");"; 
	        //3.ResultSet类，用来存放获取的结果集！！
	        statement.execute(sql);
	        con.close();

	    } catch(ClassNotFoundException e) {   
	        //数据库驱动类异常处理
	        System.out.println("Sorry,can`t find the Driver!");   
	        e.printStackTrace();   
	        } catch(SQLException e) {
	        //数据库连接失败异常处理
	        e.printStackTrace();  
	        }catch (Exception e) {
	        // TODO: handle exception
	        e.printStackTrace();
	    }finally{
	        System.out.println("数据库数据成功获取！！");
	    }
		
		return rstr;
	}
}
