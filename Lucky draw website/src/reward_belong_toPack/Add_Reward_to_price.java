package reward_belong_toPack;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import entity.Reward;
import reward_belong_toPack.*;
/**
 * Servlet implementation class Add_Reward_to_price
 */
@WebServlet("/Add_Reward_to_price")
public class Add_Reward_to_price extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Add_Reward_to_price() {
        super();
        // TODO Auto-generated constructor stub
    }
    
    public void show_item(Reward_belong_to item) {
    	System.out.println("id:"+item.getRid());
    	System.out.println("llevel:"+item.getLlevel());
    	System.out.println("nums:"+item.getNums());
    	System.out.println("\n");
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.setCharacterEncoding("utf-8");
		response.getWriter().append("Served at: ").append(request.getContextPath());
		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
		request.setCharacterEncoding("utf-8");
		List<Reward_belong_to> rblists = new ArrayList<Reward_belong_to>();
		String str_list="rlist";
		String str_nums="num";
		String str_waht="what_price";
		int nums=Integer.parseInt(request.getParameter("stepnums")); //代表了奖等的数量
		int pid=1;
		Reward_belong_toDAO tool =new Reward_belong_toDAO();
		String rs="";
		for(int i=1;i<=nums;i++) {
			String temp1 = str_list+String.valueOf(i);
			String temp2 = str_nums+String.valueOf(i);
			String temp3 = str_waht+String.valueOf(i);
			String rid = request.getParameter(temp1);
			String pnums = request.getParameter(temp2);
			String llevel = request.getParameter(temp3);
			Reward_belong_to item = new Reward_belong_to();
			item.setLlevel(Integer.parseInt(llevel));
			item.setNums(Integer.parseInt(pnums));
			item.setRid(Integer.parseInt(rid));
			item.setPid(pid);
			show_item(item);
			rblists.add(item);
			rs=tool.insert(Integer.parseInt(rid),pid,Integer.parseInt(pnums),Integer.parseInt(llevel));
		}
		if(rs.equals("right")){
			System.out.println("插入结束！！！");
			request.setAttribute("right", "插入成功!");
		}
		else {
			if(rs.equals("sql_worry!")) {
				request.setAttribute("worry1", "有同名数据，插入失败!");
			}
			else {
				request.setAttribute("worry2", "java代码出错，联系后端管理员!");
			}
		}
		request.getRequestDispatcher("add_reward_into_price.jsp").forward(request, response)  ;
		return;
			
	}

}
