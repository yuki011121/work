package haoyuNeed;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Vector;

import entity.Reward;
import entity.Price;
import reward_belong_toPack.Reward_belong_to;

public class TempDao {

	private Connection con;
    //驱动程序名
    String driver = "com.mysql.cj.jdbc.Driver";
    //URL指向要访问的数据库名mydata
    String url = "jdbc:mysql://localhost:3306/Cloud?&useSSL=false&serverTimezone=UTC";
    //MySQL配置时的用户名
    private String user = "root";
    //MySQL配置时的密码
    private String password = "W9G2T5355";
	
    public Reward selectRewardAccoringToRid(int rid)
    {
    	Reward ansReward = new Reward();
    	try {
	        //加载驱动程序
	        Class.forName(driver);
	        //1.getConnection()方法，连接MySQL数据库！！
	        con = DriverManager.getConnection(url,user,password);
	        //2.创建statement类对象，用来执行SQL语句！！
	        Statement statement = con.createStatement();
	        //要执行的SQL语句
	        String sql = "select * from Reward where rid=" + rid +";";
	        ResultSet rs = statement.executeQuery(sql);
	        
	        while(rs.next()){
	        	ansReward.setName(rs.getString("name"));
	        	ansReward.setPrice(rs.getFloat("price"));
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
	    
    	return ansReward;
    }
    
    public ArrayList<Price> selectPrice(String aid)
	{
		String sql="select * from Price where aid="+aid+";";
		
		//"select * from admain where admin_name = '" + user + "' and Pwd = '" + password + "'"
		PreparedStatement psm=null;
		ResultSet rs=null;
		Price price=null;
		ArrayList<Price> priceList=new ArrayList<Price>();
		try {
			//加载驱动程序
	        Class.forName(driver);
	        //1.getConnection()方法，连接MySQL数据库！！
	        con = DriverManager.getConnection(url,user,password);
	        //2.创建statement类对象，用来执行SQL语句！！
	        Statement statement = con.createStatement();
			rs=statement.executeQuery(sql);
			while(rs.next()) {
				price=new Price();
				price.setName(rs.getString("name"));
				price.setPid(rs.getInt("pid"));
				price.setAid(rs.getInt("aid"));
				price.setMode(rs.getInt("mode"));
				price.setEnd_date(rs.getTimestamp("End_date"));
				price.setBegin_date(rs.getTimestamp("begin_date"));
				priceList.add(price);
			}
			
		}catch(Exception e) {
			e.printStackTrace();
		}
		return priceList;
	}
    
    public double selectRewardPriceAccoringToRid(int rid)
    {
    	double ansPrice = -1;
    	try {
	        //加载驱动程序
	        Class.forName(driver);
	        //1.getConnection()方法，连接MySQL数据库！！
	        con = DriverManager.getConnection(url,user,password);
	        //2.创建statement类对象，用来执行SQL语句！！
	        Statement statement = con.createStatement();
	        //要执行的SQL语句
	        String sql = "select * from Reward where rid=" + rid +";";
	        ResultSet rs = statement.executeQuery(sql);
	        
	        while(rs.next()){
	        	ansPrice = rs.getFloat("price");
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
	    
    	return ansPrice;
    }
    
    public Vector<Price> selectPriceAccordingToAid (int aid)
    {
    	Price tempPrice = new Price();
    	Vector<Price> ansPrices = new Vector<Price>();
    	try {
	        //加载驱动程序
	        Class.forName(driver);
	        //1.getConnection()方法，连接MySQL数据库！！
	        con = DriverManager.getConnection(url,user,password);
	        //2.创建statement类对象，用来执行SQL语句！！
	        Statement statement = con.createStatement();
	        //要执行的SQL语句
	        String sql = "select * from price where aid=" + aid +";";
	        ResultSet rs = statement.executeQuery(sql);
	        
	        while(rs.next()){
	        	tempPrice.setName(rs.getString("name"));
	        	tempPrice.setPid(rs.getInt("pid"));
	        	tempPrice.setAid(rs.getInt("aid"));
	        	tempPrice.setMode(rs.getInt("mode"));
	        	tempPrice.setEnd_date(rs.getTimestamp("End_date"));
	        	tempPrice.setBegin_date(rs.getTimestamp("begin_date"));
	        	ansPrices.add(tempPrice);
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
	    
    	return ansPrices;
    }
    
    public Vector<Reward_belong_to> selectRBTAccordingToPid(int pid)
    {
    	Vector<Reward_belong_to> ansRBT = new Vector<Reward_belong_to>();
    	Reward_belong_to tempRBT = null;
    	
    	
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
	        
	        System.out.println(rs.toString());
	        
	        while(rs.next()){
	        	tempRBT = new Reward_belong_to();
	        	tempRBT.setPid(rs.getInt("pid"));
	        	tempRBT.setRid(rs.getInt("rid"));
	        	tempRBT.setNums(rs.getInt("nums"));
	        	tempRBT.setLlevel(rs.getInt("llevel"));
            
//	        	System.out.println("\n"+rs.getInt("pid"));
//	        	System.out.println(rs.getInt("rid"));
//	        	System.out.println(rs.getInt("nums"));
//	        	System.out.println(rs.getInt("llevel"));
//	        	
//	        	System.out.println("\n"+tempRBT.getPid());
//	        	System.out.println(tempRBT.getRid());
//	        	System.out.println(tempRBT.getNums());
//	        	System.out.println(tempRBT.getLlevel());
	        	ansRBT.addElement(tempRBT);
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
    	
    	for(int i = 0;i < ansRBT.size(); i++)
    	{
    		tempRBT=ansRBT.get(i);
        	System.out.println("\n"+tempRBT.getPid());
        	System.out.println(tempRBT.getRid());
        	System.out.println(tempRBT.getNums());
        	System.out.println(tempRBT.getLlevel());
    	}
    	
    	return ansRBT;
    }
}
