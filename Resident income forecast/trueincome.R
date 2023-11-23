library(caret)  
library(dplyr)
library(ggplot2)
library(reshape2)
library(grid)
# install.packages("gridExtar")
#载入数据
data <- read.table("D://R-data/Income.data", header = F, sep = ",", na.strings = " ?")
#查看数据类型
summary(data)
str(data)
#给列命名
names(data) <- c("age","workclass","fnlwgt","education","educational.num","marital.status","Occupation","Relationship","race","Sex","capital.gain","capital.loss","Hours.per.week","native.country","income")
names(data)
head(data)

#探索数据
library(ggplot2)
#查看年龄和收入的柱状图
ggplot(data, aes(age)) + geom_histogram(aes(fill = income), color = "black",binwidth = 1)+
  scale_x_continuous(limits=c(20,90), breaks=seq(20,90,5)) +
  xlab("Age") +
  ylab("No of people by age")
#结论：收入大于50K的人群年龄集中在30-50岁之间

#查看年龄和性别的柱状图
ggplot(data) + aes(x=as.numeric(age),group=Sex, fill=Sex) +geom_histogram(binwidth=2,color='black')
#结论：数据中男性占比更大，年龄集中在20-50岁

#查看每周工作小时数
ggplot(data, aes(Hours.per.week)) + geom_histogram()
#结论：最高频的数据是每周工作40h（平均每天工作八小时，很良心）

#更直观地方法：箱型图输出
ggplot(aes(x = factor(0), y = Hours.per.week),
       data = data) + 
  geom_boxplot() +
  stat_summary(fun.y = mean, 
               geom = 'point', 
               shape = 19,
               color = "red",
               cex = 2) +
  scale_x_discrete(breaks = NULL) +
  scale_y_continuous(breaks = seq(0, 100, 5)) + 
  xlab(label = "") +
  ylab(label = "working hours x week") +
  ggtitle("Box Plot of working hours x week") 
#结论：平均工作小时数为40标记为箱线图上的红点，并且至少50%参与调查的人，每周工作40至45小时：

#查看资本损失
ggplot(data, aes(capital.loss)) + geom_histogram()
#结论：资本损失可能对分类没有用，因为它非常倾斜并且主要集中在零值

#查看资本增益
ggplot(data, aes(capital.gain)) + geom_histogram()
#结论：资本增益可能对分类没有用，因为它非常倾斜并且主要集中在零值


str(data)


#数据处理
#缺失值处理，填补有缺失值的部分
sapply(data, function(x) sum(is.na(x)))
data$workclass[is.na(data$workclass)]   <- " Private"
data$Occupation[is.na(data$Occupation)] <- " Prof-Specialty"
data$native.country[is.na(data$native.country)]       <- " United-States"
sapply(data, function(x) sum(is.na(x)))

#异常值处理

Outlier1 <- boxplot (data$age, plot = FALSE)$out
data <- data[-which(data$age %in% Outlier1 ),]

Outlier2 <- boxplot (data$fnlwgt, plot = FALSE)$out
data <- data[-which(data$fnlwgt %in% Outlier2 ),]

Outlier3 <- boxplot (data$educational.num, plot = FALSE)$out
data <- data[-which(data$educational.num %in% Outlier3 ),]

Outlier6 <- boxplot (data$Hours.per.week, plot = FALSE)$out
data <- data[-which(data$Hours.per.week %in% Outlier6 ),]

#将收入是否大于50K转换为0/1表示  >50K
data$income<-ifelse(data$income==' >50K',1,0)

#将chr型改为factor型
data <- data %>% 
  mutate_if(is.character,as.factor)
str(data)


library(caTools)
split <- sample.split(data$income, SplitRatio = 0.7)
#因为在几次尝试随机划分时，发现如果Holand-Netherlands没被划分到训练集，预测时层数不匹配就会报错，所以训练集中强制加入了该数据
train <- subset(data, split == TRUE | native.country==' Holand-Netherlands')
test <- subset(data, split == FALSE)
#10折交叉验证
train.control <- trainControl(method="cv",number=10)
log.model <- glm(income ~ ., family = binomial(), train)
summary(log.model)
prediction <- predict(log.model, test, type = "response")
#混淆矩阵
cm<-with(train,table(test$income, prediction >= 0.5))
cm
#精度
trainacc<- (cm[1,1]+cm[2,2])/(cm[1,1]+cm[2,2]+cm[1,2]+cm[2,1])
trainacc
#准确率
trainprecision<- cm[2,2]/(cm[2,2]+cm[1,2])
trainprecision
#召回率
trainrecall<-cm[2,2]/(cm[2,2]+cm[2,1])
trainrecall
#F-sscore
trainfs<-2*(trainacc*trainrecall)/(trainacc+trainrecall)
trainfs

library(knitr) 
library(ROCR)  
eval <- prediction(prediction,test$income)
plot(performance(eval,"tpr","fpr"))
print(attributes(performance(eval,'auc'))$y.values[[1]])

summary(log.model)$coefficients
kable(summary(log.model)$coefficients, longtable=TRUE, digits = 6)
#改进

data$workclass <- as.character(data$workclass)
data$workclass[data$workclass == " Without-pay" | 
                 data$workclass == " Never-worked"] <- " Unemployed"

data$workclass[data$workclass == " State-gov" |
                 data$workclass == " Local-gov"] <- " SL-gov"

data$workclass[data$workclass == " Self-emp-inc" |
                 data$workclass == " Self-emp-not-inc"] <- " Self-employed"

table(data$workclass)

table(data$marital.status)
data$marital.status <- as.character(data$marital.status)

data$marital.status[data$marital.status == " Married-AF-spouse" |
                      data$marital.status == " Married-civ-spouse" |
                      data$marital.status == " Married-spouse-absent"] <- " Married"

data$marital.status[data$marital.status == " Divorced" |
                      data$marital.status == " Separated" |
                      data$marital.status == " Widowed"] <- " Not-Married"
table(data$marital.status)

table(data$education)
data$education <- as.character(data$education)
data$education[data$education == " 12th" |
                      data$education == " Preschool" |
                      data$education == " 1st_4th" |
                      data$education == " 10th" |
                      data$education == " 5th_6th"|
                      data$education == " 7th-8th" |
                      data$education == " 9th" |
                      data$educations == " 11th"] <- " Schooling"
data$education[data$education == " Bachelors" |
                 data$education == " HS_grad" |
                 data$education == " Some_college" ] <- " Graduate"
data$education[data$education == " Assoc_acdm" |
                 data$education == " Assoc_voc" |
                 data$education == " Prof_school" ] <- " Masters"

table(data$Occupation)
data$Occupation <- as.character(data$Occupation)
data$Occupation[data$Occupation == " Adm_clerical" |
                  data$Occupation == " Sales" |
                  data$Occupation == " Transport_moving" |
                  data$mOccupation == " Handlers_cleaners"] <- " Admin/Clerical"
data$Occupation[data$Occupation == " Farming_fishing" |
                   data$Occupation == " Protective_serv" |
                   data$Occupation == " Armed_Forces" |
                   data$Occupation == " Other_service" |
                   data$mOccupation == " Priv_house_serv"] <- " others"
data$Occupation[data$Occupation == " Machine_op_inspct" |
                   data$Occupation == " Tech_support" ] <- " Technical"
data$Occupation[data$Occupation == " Exec_managerial" |
                  data$Occupation == " Prof_specialty" ] <- " Managerial"

#
data <- data %>% 
  mutate_if(is.character,as.factor)

log2.model <- glm(income~age+workclass+fnlwgt+education+educational.num+marital.status+Occupation+Relationship+race+Sex+Hours.per.week+capital.gain+capital.loss, family = binomial(), train)
summary(log2.model)
prediction <- predict(log2.model, test, type = "response")

#混淆矩阵
cm<-with(train,table(test$income, prediction >= 0.5))
cm
#精度
trainacc<- (cm[1,1]+cm[2,2])/(cm[1,1]+cm[2,2]+cm[1,2]+cm[2,1])
trainacc
#准确率
trainprecision<- cm[2,2]/(cm[2,2]+cm[1,2])
trainprecision
#召回率
trainrecall<-cm[2,2]/(cm[2,2]+cm[2,1])
trainrecall
#F-sscore
trainfs<-2*(trainacc*trainrecall)/(trainacc+trainrecall)
trainfs







