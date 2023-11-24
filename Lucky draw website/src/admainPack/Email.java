package admainPack;

import java.security.GeneralSecurityException;
import java.util.Properties;
import javax.mail.Authenticator;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
import com.sun.mail.util.MailSSLSocketFactory;

public class Email
{
	
	
    public static final String URL = "http://localhost:8080/newturn/";//项目主页
    public static final int TIMELIMIT = 1000*60*60*24; //激活邮件过期时间24小时
    public static final String TITLE = "iClass账户激活邮件";
   /* public static final String HOST = "smtp.163.com";
    public static final String SMTP = "smtp";*/

	
    public static void send(int id, String name,String email,int llevel) throws GeneralSecurityException 
    {
        // 收件人邮箱,不仅仅QQ邮箱
        String to = email;

        // 发件人电子邮箱,你生成授权码的QQ邮箱
        String from = "2018191080@qq.com";

        // 指定发送邮件的主机为 smtp.qq.com
        String host = "smtp.qq.com";  //QQ 邮件服务器

        // 获取系统属性
        Properties properties = System.getProperties();

        // 设置邮件服务器
        properties.setProperty("mail.smtp.host", host);

        properties.put("mail.smtp.auth", "true");
        MailSSLSocketFactory sf = new MailSSLSocketFactory();
        sf.setTrustAllHosts(true);
        properties.put("mail.smtp.ssl.enable", "true");
        properties.put("mail.smtp.ssl.socketFactory", sf);
        // 获取默认session对象
        Session session = Session.getDefaultInstance(properties, new Authenticator(){
            public PasswordAuthentication getPasswordAuthentication()
            {
                return new PasswordAuthentication("2018191080@qq.com", "hcylnneovhvydfhd"); //登录邮箱及授权码
            }
        });
        String token = to+System.currentTimeMillis();
        /*String content = "<p>尊敬的"+name+"您好 !O(∩_∩)O~~<br><br>欢迎加入云抽!<br><br>帐户需要激活才能使用，赶紧激活成为云抽正式的一员吧:)<br><br>请在24小时内点击下面的链接立即激活帐户："
                +"/n <br><a href='"+URL+"activatemail.jsp?token="+token+"/n &email="+to+"'>"
                +URL+"activatemail.jsp?token="+token+"&email="+to+"</a></p>";*/
        //String content = "http://localhost:8080/newturn/CheckRegister_Admain?email=2018191080%40qq.com&name=1&pass=1&pass2=1&llevel=1";
        /*"<p>您好 O(∩_∩)O~~<br><br>欢迎加入XXX!<br><br>帐户需要激活才能使用，赶紧激活成为XXX正式的一员吧:)<br><br>请在24小时内点击下面的链接立即激活帐户："
                                   +"<br><a href='http://???/jihuo?token="+token+"&email="+email+"'>"
                                   + "http://???/jihuo?token="+token+"&email="+email+"</a></p>"*/
        String content ="尊敬的"+name+"您好 !O(∩_∩)O~~欢迎加入云抽!您的ID是:"+id+"帐户需要激活才能使用，赶紧激活成为云抽正式的一员吧:)请在24小时内点击下面的链接立即激活帐户："
                +URL+"ActiveEmail?email="+email+"&llevel="+llevel;
        try{
            // 创建默认的 MimeMessage 对象
            MimeMessage message = new MimeMessage(session);

            // Set From: 头部头字段
            message.setFrom(new InternetAddress(from));

            // Set To: 头部头字段
            message.addRecipient(Message.RecipientType.TO, new InternetAddress(to));

            // Set Subject: 头部头字段
            message.setSubject("云抽欢迎您的加入！");

            // 设置消息体
            
            message.setContent(content, "text/html;charset=utf-8");
            message.setText(content);
            // 发送消息
            Transport.send(message);
           // System.out.println("Sent message successfully");
            return;
        }catch (MessagingException mex) {
            mex.printStackTrace();
        }
    }
}
