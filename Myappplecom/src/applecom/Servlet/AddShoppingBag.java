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

import applecom.db.DBServlet;
import applecom.entity.Order;

public class AddShoppingBag extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public AddShoppingBag() {
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
		request.getRequestDispatcher("iphone-13pro.jsp").forward(request, response);
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

		/*response.setContentType("text/html");
		PrintWriter out = response.getWriter();
		out.println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
		out.println("<HTML>");
		out.println("  <HEAD><TITLE>A Servlet</TITLE></HEAD>");
		out.println("  <BODY>");
		out.print("    This is ");
		out.print(this.getClass());
		out.println(", using the POST method");
		out.println("  </BODY>");
		out.println("</HTML>");
		out.flush();
		out.close();*/
		
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html);charset=UTF-8");
		
		Order order=new Order();
		//获取注册的姓氏
		String email=(String)request.getSession().getAttribute("AppleID");
		
		String phoneinfo[]=request.getParameter("screensize").split("\\s+");
		//获取注册的名字
		String phonename=phoneinfo[1];
		//获取注册的地区
		String screensize=phoneinfo[0];
	    //获取注册的生日
	    String color = request.getParameter("color");
	    
	    order.setemail(email);
	    order.setphonename(phonename);
	    order.setscreensize(screensize);
	    order.setcolor(color);
	    
	    try {
			//获取数据库的连接，并将user中的数据插入数据库中
			//查询当前的用户名和邮箱在数据库中是否已经被注册过
			DBServlet conn=new DBServlet();
			//与数据库获取连接
			Connection connection=conn.getConne();
		    String sql1="insert into orders (email,phonename,screensize,color) values(?,?,?,?)";
		    PreparedStatement statement=connection.prepareStatement(sql1);
			statement.setString(1, email);
			statement.setString(2, phonename);
			statement.setString(3, screensize);
			statement.setString(4, color);          
		    int result=statement.executeUpdate();
			if(result==1)
		    {
			     System.out.println("加入购物袋成功");
			     request.getSession().setAttribute("msg_add", "加入购物袋成功");
			     request.getRequestDispatcher("../ListOrders").forward(request, response);
			}else{ 
			     System.out.println("加入购物袋失败");
			     request.getSession().setAttribute("msg_add", "加入购物袋失败");
			     request.getRequestDispatcher("iphone-13pro.jsp").forward(request, response);
			}         
			//关闭数据库连接
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
