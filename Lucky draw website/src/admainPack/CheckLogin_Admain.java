package admainPack;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import entity.Admain;
/**
 * Servlet implementation class CheckLogin
 */
@WebServlet("/CheckLogin")
public class CheckLogin_Admain extends HttpServlet {
	private static final long serialVersionUID = 1L;
	HttpSession session;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public CheckLogin_Admain() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
    
    
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.setCharacterEncoding("utf-8");
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		//
		
		
		/*
		String level=request.getParameter("llevel");
		int llevel  = Integer.valueOf(level);
		if(llevel<1||llevel>2){
			request.setAttribute("error3", "请输入正确的级别");
			request.getRequestDispatcher("/index.jsp").forward(request, response);
		}*/
		
		int llevel =1;
		String id=request.getParameter("id");
		
		String pass=request.getParameter("pass");
		
		AdmainDao admainDao = new AdmainDao();
		System.out.println("进入admain!!!");
		Admain user;
		if(id.contains("@"))
			user= admainDao.LoginByEmail(id, llevel);
		else
			user=admainDao.Login(id,llevel);
		
		if (user!=null) {
			
			if(user.getStatus()==0){
				request.setAttribute("error3", "账户未激活，请先前往邮箱激活后登录!");
				request.getRequestDispatcher("/login.jsp").forward(request, response);
			}
			
			else if( !user.getPass().equals(pass) ) {
				
				//System.out.println("用户存在,密码错误");
				request.setAttribute("error2", "密码错误");
				//response.sendRedirect("/price_setting.jsp");
				request.getRequestDispatcher("/login.jsp").forward(request, response);
			}
			
			else{
				//System.out.println("登陆成功！");
				//request.setAttribute("error2",admain.getPass()+" "+upass+" "+admain.getPass().getClass().toString()+" "+upass.getClass().toString() );
				if(llevel==1)
					
				{
					session =request.getSession();
					session.setAttribute("id", id);  //将id信息存入到session中
					session.setAttribute("llevel", llevel);
					request.getRequestDispatcher("./index_.jsp").forward(request, response);
					
				}	
				else {
					
					session =request.getSession();
					session.setAttribute("id", id);  //将id信息存入到session中
					session.setAttribute("llevel", llevel);
					request.getRequestDispatcher("./index_.jsp").forward(request, response);
				}
	
			}
			
		}
		else {
			request.setAttribute("error1", "用户名或用户等级不正确");
			request.getRequestDispatcher("/login.jsp").forward(request, response); 
			//https://www.cnblogs.com/damoblog/p/8250345.html
			//前后两个页面 有数据传递 用请求转发，没有则用重定向。
			//比如servlet查询了数据需要在页面显示，就用请求转发。
			//比如servlet做了update操作跳转到其他页面，就用重定向。
		}
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
