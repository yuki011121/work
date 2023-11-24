package reward_belong_toPack;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Vector;

public class Reward_belong_toDAO {
	
	//声明Connection对象
    private Connection con;
    //驱动程序名
    String driver = "com.mysql.cj.jdbc.Driver";
    //URL指向要访问的数据库名mydata
    String url = "jdbc:mysql://localhost:3306/Cloud?&useSSL=false&serverTimezone=UTC";
    //MySQL配置时的用户名
    private String user = "root";
    //MySQL配置时的密码
    private String password = "W9G2T5355";
    //遍历查询结果集
    
    public Vector<Reward_belong_to> select(int pid)
    {
    	Vector<Reward_belong_to> ansRBT = new Vector();
    	try {
	        //加载驱动程序
	        Class.forName(driver);
	        //1.getConnection()方法，连接MySQL数据库！！
	        con = DriverManager.getConnection(url,user,password);
	        //2.创建statement类对象，用来执行SQL语句！！
	        Statement statement = con.createStatement();
	        //要执行的SQL语句
	        String sql = "select * from Reward_belong_to where pid=" + pid +";";
	        ResultSet rs = statement.executeQuery(sql);
	        while(rs.next()){
	        	Reward_belong_to tempRBT = new Reward_belong_to();
	        	tempRBT.setPid(Integer.parseInt(rs.getString("pid")));
	        	tempRBT.setRid(Integer.parseInt(rs.getString("rid")));
	        	tempRBT.setNums(Integer.parseInt(rs.getString("nums")));
	        	tempRBT.setLlevel(Integer.parseInt(rs.getString("llevel")));
	        	ansRBT.add(tempRBT);
	        }
	        
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
    	
    	return ansRBT;
    }
	
	public void delete(int rid, int pid, int nums, int llevel)
	{
		try {
	        //加载驱动程序
	        Class.forName(driver);
	        //1.getConnection()方法，连接MySQL数据库！！
	        con = DriverManager.getConnection(url,user,password);
	        //2.创建statement类对象，用来执行SQL语句！！
	        Statement statement = con.createStatement();
	        //要执行的SQL语句
	        String sql = "delete from reward_belong_to where rid="+ rid + "and pid=" + pid + ';'; 

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

	public String insert(int rid, int pid, int nums, int llevel)
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
	        String sql = "insert into reward_belong_to (rid, pid, nums, llevel) values ("
	        		+ rid + ',' + pid + ',' + nums + ',' + llevel +");"; 
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
	        return "sql_worry!";
	        
	        }catch (Exception e) {
	        // TODO: handle exception
	        e.printStackTrace();
	        return "java_worry!";
	    }finally{
	        System.out.println("数据库数据成功获取！！");
	    }
		
		return "right";
	}
	
}
