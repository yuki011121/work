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
import applecom.entity.User;

public class RegisterServlet extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public RegisterServlet() {
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

/*		response.setContentType("text/html");
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
		
		// 跳转到register.jsp
		request.getRequestDispatcher("/register.jsp").forward(request, response);
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
		
		request.setCharacterEncoding("UTF-8");
		response.setContentType("text/html);charset=UTF-8");
		System.out.println("注册人的姓氏是: "+request.getParameter("surname"));
		
	    // 获取实体User中的变量，将变量插入到数据库中，完成注册
		User user=new User();
		//获取注册的姓氏
		String surname=request.getParameter("surname");
		//获取注册的名字
		String givenname=request.getParameter("givenname");
		//获取注册的地区
		String region=request.getParameter("region");
		//获取注册的生日
		String birthday = request.getParameter("birthday");
		//获取注册的邮箱
		String email=request.getParameter("email");
		//获取注册的密码
		String pwd=request.getParameter("pwd");
		//获取注册的电话
		String tel=request.getParameter("tel");
		// 将获取到的注册信息放入user中
		user.setsurname(surname);
		user.setgivenname(givenname);
		user.setregion(region);
		user.setbirthday(birthday);
		user.setemail(email);
		user.setpwd(pwd);
		user.settel(tel);
		
		try {
			//获取数据库的连接，并将user中的数据插入数据库中
			//查询当前的用户名和邮箱在数据库中是否已经被注册过
			String sql="select id from users where email=?";
			DBServlet conn=new DBServlet();
			//与数据库获取连接
			  Connection connection=conn.getConne();
			//SQL语句被预编译并存储在PreparedStatement对象中
			PreparedStatement statement=connection.prepareStatement(sql);
			//将第一个问号的name值添加进去
			statement.setString(1, email);
			//执行sql语句
			ResultSet rs=statement.executeQuery();
			
			//判断rs集合中是否为null,为null表示数据库中不存在重复的
			//否则存在重复数据，注册失败
			if(rs.next())
			{
			System.out.println("注册失败，用户名或者邮箱已经存在，");
			request.getSession().setAttribute("remind", "注册失败,邮箱已经存在");
			//重新跳转到注册页面
			request.getRequestDispatcher("register.jsp").forward(request, response);;
		    }
			else
			{
				String sql1="insert into users (surname,givenname,region,birthday,email,pwd,tel) values(?,?,?,?,?,?,?)";
			    statement=connection.prepareStatement(sql1);
			    statement.setString(1, surname);
			    statement.setString(2, givenname);
			    statement.setString(3, region);
			    statement.setString(4, birthday);
			    statement.setString(5, email);
			    statement.setString(6, pwd);
			    statement.setString(7, tel);
			             
		        int result=statement.executeUpdate();
			    if(result==1)
		        {
			         System.out.println("注册成功，欢迎你:"+surname+"先生/女士");
			         request.getSession().setAttribute("remind", "注册成功");
			         request.getRequestDispatcher("login.jsp").forward(request, response);
			     }
			     else
			     { 
			         System.out.println("注册失败");
			         request.getSession().setAttribute("remind", "注册失败");
			         request.getRequestDispatcher("register.jsp").forward(request, response);
			         }
			             
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
