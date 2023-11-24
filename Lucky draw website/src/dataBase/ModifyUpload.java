package dataBase;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.util.Iterator;
import java.util.List;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import dataBase.ConnectionManager;

/**
 * Servlet implementation class ModifyUpload
 */
@WebServlet("/ModifyUpload")
public class ModifyUpload extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private static final int MAX_MEMORY_SIZE = 5*2*1024;	//设置内存大小
	private static final File REPOSITORY_PATH = new File("C:\\Users\\Administrator\\Desktop");//设置临时存放目录
	
	File file;
	Connection conn =ConnectionManager.getConnection();
	ServletContext application;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ModifyUpload() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
    
    @SuppressWarnings("unchecked")
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
    	response.setCharacterEncoding("UTF-8");
    	System.out.println("进入ModifyUpload");
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		//PrintWriter out =response.getWriter();
		application = this.getServletContext();
		HttpSession session  = request.getSession();
		//String aid= (String)session.getAttribute("id");
		String aid="1";

		
		DiskFileItemFactory factory =new DiskFileItemFactory(); //创建工厂
		factory.setSizeThreshold(MAX_MEMORY_SIZE);	//设置内存大小
		factory.setRepository(REPOSITORY_PATH);			//设置临时存储路径
		ServletFileUpload servletFileUpload = new ServletFileUpload(factory); 	//创建文件上传控制器
		servletFileUpload.setHeaderEncoding("UTF-8");  //防止文件名乱码
		try {
			List items = servletFileUpload.parseRequest(request);  //获取所有表单项存储在items
			Iterator iter = items.iterator();
			while(iter.hasNext()) {
				FileItem item = (FileItem) iter.next();
				if(!item.isFormField()) {//如果不是普通的表单类型,即文件类型
					String filename=item.getName();
					long size =item.getSize();
					if (filename ==null || filename.equals("") && size==0) {
						continue;
					}
					int index=filename.lastIndexOf("\\");
					if(index!=-1) {
						filename=filename.substring(index+1);
					}
					file = new File(application.getRealPath("/")+"FileUpload/"+filename);
					item.write(file);	//将文件写到制定路径中去
					
				}
				else {
					aid=item.getString();
				}
			}
			                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
		}catch(Exception e) {
			response.setCharacterEncoding("UTF-8");
			System.out.println("上传出错，原因如下！！");
			System.out.println(e.toString());
			e.printStackTrace();
		}
		//response.getWriter().append("success");
		System.out.println("退出ModifyUpload");
		//response.getWriter().append("seucess");
		//request.getRequestDispatcher("addReward.jsp").forward(request, response);
		return;
		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
