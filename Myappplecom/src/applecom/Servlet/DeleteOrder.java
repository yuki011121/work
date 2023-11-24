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

public class DeleteOrder extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public DeleteOrder() {
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
		doPost(request, response);
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
		int O_id=Integer.parseInt(request.getParameter("O_id"));
		try {
			//获取数据库的连接，并将user中的数据插入数据库中
			//查询当前的用户名和邮箱在数据库中是否已经被注册过
			DBServlet conn=new DBServlet();
			//与数据库获取连接
			Connection connection=conn.getConne();
		    String sql1="delete from orders where O_id=?";
		    PreparedStatement statement=connection.prepareStatement(sql1);
		    statement.setInt(1, O_id);
			statement.executeUpdate();
            System.out.println("删除执行完了");
            request.getRequestDispatcher("ListOrders").forward(request,response);
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
