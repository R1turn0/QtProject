#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout> 	// 水平布局
#include <QVBoxLayout>	// 垂直布局
#include <QWidget>		// 窗口

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	QLabel* infoLabel = new QLabel;
	QLabel* openLabel = new QLabel;
	QLineEdit* cmdLineEdit = new QLineEdit;
	QPushButton* commitButton = new QPushButton;
	QPushButton* cancelButton = new QPushButton;
	QPushButton* browseButton = new QPushButton;
	
	infoLabel -> setText("input cmd:");
	openLabel -> setText("open");
	commitButton -> setText("commit");
	cancelButton -> setText("cancel");
	browseButton -> setText("browse");
	
	// 水平布局对象
	QHBoxLayout* cmdLayout = new QHBoxLayout;
	cmdLayout -> addWidget(openLabel);
	cmdLayout -> addWidget(cmdLineEdit);
	
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout -> addWidget(commitButton);
	buttonLayout -> addWidget(cancelButton);
	buttonLayout -> addWidget(browseButton);
	
	// 垂直布局对象
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout -> addWidget(infoLabel);
	mainLayout -> addLayout(cmdLayout);
	mainLayout -> addLayout(buttonLayout);
	
	// 创建窗口
	QWidget w;
	w.setLayout(mainLayout);
	w.show();
	
	return app.exec();
}
