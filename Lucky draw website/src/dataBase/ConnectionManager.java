package dataBase;
import java.sql.*;

public class ConnectionManager {
    private static final String driverClass = "com.mysql.cj.jdbc.Driver";
    private static final String url = "jdbc:mysql://localhost:3306/choujiang?allowPublicKeyRetrieval=true&useSSL=false&serverTimezone=GMT";
    private static final String username = "root";
    private static final String password = "miao";

    public static Connection getConnection()
    {
    	Connection con= null;
    	try {
    		Class.forName(driverClass);
    		con =DriverManager.getConnection(url,username,password);
    	}catch(Exception e) {
    		e.printStackTrace();
    	}
    	return con;
    }
    
    
    public static void closeConnection(Connection con) {
    	try {
    		if(con!=null) {
    			con.close();
    			con=null;
    		}
    	}
    	catch(SQLException sqlEx) {
    		sqlEx.printStackTrace();
    	}
    }
    
    public static void closeResultSet(ResultSet rs) {
    	try {
    		if(rs !=null) {
    			rs.close();
    			rs=null;
    		}
    	}
    	catch(SQLException sqlEx) {
    		sqlEx.printStackTrace();
    	}
    }
    
    public static void closeStatement (PreparedStatement pst) {
    	try {
    		if(pst!=null) {
    			pst.close();
    			pst=null;
    		}
    	}catch(SQLException sqlEx) {
    		sqlEx.printStackTrace();
    	}
    }
    
}
