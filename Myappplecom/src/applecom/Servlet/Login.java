package applecom.Servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import applecom.db.DBServlet;
import applecom.entity.Order;

public class Login extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public Login() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		/*response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
		out.println("<HTML>");
		out.println("  <HEAD><TITLE>A Servlet</TITLE></HEAD>");
		out.println("  <BODY>");
		out.print("    This is ");
		out.print(this.getClass());
		out.println(", using the GET method");
		out.println("  </BODY>");
		out.println("</HTML>");
		out.flush();
		out.close();*/
		// 跳转到login.jsp
		request.getRequestDispatcher("/login.jsp").forward(request, response);
	}

	/**
	 * The doPost method of the servlet. <br>
	 *
	 * This method is called when a form has its tag value method equals to post.
	 * 
	 * @param request the request send by the client to the server
	 * @param response the response send by the server to the client
	 * @throws ServletException if an error occurred
	 * @throws IOException if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

//		response.setContentType("text/html");
//		PrintWriter out = response.getWriter();
//		out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
//		out.println("<HTML>");
//		out.println("  <HEAD><TITLE>A Servlet</TITLE></HEAD>");
//		out.println("  <BODY>");
//		out.print("    This is ");
//		out.print(this.getClass());
//		out.println(", using the POST method");
//		out.println("  </BODY>");
//		out.println("</HTML>");
//		out.flush();
//		out.close();
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html);charset=UTF-8");
		System.out.println("登录人的Apple ID是: "+request.getParameter("AppleID"));
		
		
		String email=request.getParameter("AppleID");
		
		String pwd = request.getParameter("password");
		
		//登录是否成功
		boolean isLogin = false;
		
		try {
			//获取数据库的连接，并将user中的数据插入数据库中
			//查询当前的用户名和邮箱在数据库中是否已经被注册过
			String sql="select * from users where email=? and pwd=?";
			DBServlet conn=new DBServlet();
			//与数据库获取连接
			Connection connection=conn.getConne();
			//SQL语句被预编译并存储在PreparedStatement对象中
			PreparedStatement statement=connection.prepareStatement(sql);
			//将第一个问号的name值添加进去
			statement.setString(1, email);
			statement.setString(2, pwd);
			//执行sql语句
			ResultSet rs=statement.executeQuery();
			
			//判断rs集合中是否为null,为null表示数据库中不存在重复的
			//否则存在重复数据，注册失败
			if(rs.next())
			{
				isLogin=true;//登录成功
				System.out.println("登录成功");
		    } else {
				isLogin=false;//登录失败
		    }
			if(isLogin){
				HttpSession session=null;//清除页面滞留的session，这样点击退出以后，下次登录确保重新获取新的用户名
				session = request.getSession();
				session.setAttribute("AppleID",email);
			    String status=(String)session.getAttribute("status");
			    if(status=="buyiphone13pro"){
			    	request.getRequestDispatcher("/buy/iphone-13pro.jsp").forward(request, response);
			    } else if (status=="buyiphone13"){
			    	request.getRequestDispatcher("/buy/iphone-13.jsp").forward(request, response);
			    } else{
			    	request.getRequestDispatcher("ListOrders").forward(request, response);
			    }
			    session.setAttribute("status","");
			}else{
				HttpSession wrongidpwd=null;
				wrongidpwd = request.getSession();
				wrongidpwd.setAttribute("wrongidpwd","帐号或密码错误");
				request.getRequestDispatcher("login.jsp").forward(request, response);
			}
			         
			     //关闭数据库连接
			     rs.close();
			     statement.close();
			     connection.close();
		} catch (SQLException e) {
			   // TODO Auto-generated catch block
			    System.out.println("数据库连接失败");
			    e.printStackTrace();
		}
	}

	/**
	 * Initialization of the servlet. <br>
	 *
	 * @throws ServletException if an error occurs
	 */
	public void init() throws ServletException {
		// Put your code here
	}

}
