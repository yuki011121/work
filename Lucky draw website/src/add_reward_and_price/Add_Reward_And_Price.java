package add_reward_and_price;

import java.io.IOException;
import java.security.GeneralSecurityException;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import admainPack.AdmainDao;
import admainPack.Email;
import entity.Admain;

/**
 * Servlet implementation class Add_Reward_And_Price
 */
@WebServlet("/Add_Reward_And_Price")
public class Add_Reward_And_Price extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Add_Reward_And_Price() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
		
			/*
		String name=request.getParameter("name");		
		float price= Float.parseFloat(request.getParameter("price"));
		int llevel =Integer.parseInt(request.getParameter("llevel"));
		int  nums=Integer.parseInt(request.getParameter("nums"));
		
		if(!pass.equals(pass2)){
			request.setAttribute("error6", "前后密码不一致！");
			request.getRequestDispatcher("/index.jsp").forward(request, response);
		}


		AdmainDao admainDao = new AdmainDao();
		Admain user= admainDao.LoginByEmail(email,llevel);

		if(llevel<1||llevel>2){
			request.setAttribute("error3", "请输入级别");
			request.getRequestDispatcher("/signup.jsp").forward(request, response);
		}

		if (user!=null&&user.getStatus()==1) {
			//注册表中有且已经激活
				request.setAttribute("error7", "该邮箱已注册，请重新输入或找回密码");
				request.getRequestDispatcher("/signup.jsp").forward(request, response);
				return;
		}
		else {//注册表中没有
			try {//注册表中没有或尚未激活
				
				if(user==null)
					admainDao.Register(name, pass, email, llevel);
				
				Email.send(Integer.valueOf(user.getId()),name,email,llevel);
				//request.getRequestDispatcher("/activatemail.jsp").forward(request, response);
				request.setAttribute("stats", "邮件已经发出");
				//request.getRequestDispatcher("/signup.jsp").forward(request, response);
				return;
			} catch (GeneralSecurityException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		
		*/
		
		
		
		
		
		
		
		
		
	}

}
