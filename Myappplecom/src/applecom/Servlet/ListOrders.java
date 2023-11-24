package applecom.Servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import applecom.db.DBServlet;
import applecom.entity.Order;

public class ListOrders extends HttpServlet {

	/**
	 * Constructor of the object.
	 */
	public ListOrders() {
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
		
		String email=(String)request.getSession().getAttribute("AppleID");
		ResultSet resultSet=null;
		List<Order> orders=new ArrayList<Order>();
		try {
			//获取数据库的连接，并将user中的数据插入数据库中
			//查询当前的用户名和邮箱在数据库中是否已经被注册过
			DBServlet conn=new DBServlet();
			//与数据库获取连接
			Connection connection=conn.getConne();
		    String sql1="select * from orders where email=?";
		    PreparedStatement statement=connection.prepareStatement(sql1);
			statement.setString(1, email);
			resultSet=statement.executeQuery();
			while(resultSet.next()){
				Order order=new Order();
				order.setO_ID(resultSet.getInt("O_id"));
				order.setemail(email);
				order.setphonename(resultSet.getString("phonename"));
				
				order.setscreensize(resultSet.getString("screensize"));
				order.setcolor(resultSet.getString("color"));
				orders.add(order);
				System.out.println(order.toString());
			}
			
			HttpSession session=null;
			session=request.getSession();
            session.setAttribute("orderlist",orders);
            request.getRequestDispatcher("bag.jsp").forward(request,response);
            System.out.println("执行完了");
			//关闭数据库连接
			resultSet.close();
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
