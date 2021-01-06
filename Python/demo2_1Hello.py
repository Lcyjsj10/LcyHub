import sys
from PyQt5 import QtCore, QtGui, QtWidgets

app=QtWidgets.QApplication(sys.argv)
widgetHello=QtWidgets.QWidget()
widgetHello.resize(280,150)
widgetHello.setWindowTitle("Demo2_1")

LabHello=QtWidgets.QLabel(widgetHello)
LabHello.setText("Hello World,PyOt5")
font=QtGui.QFont()
font.setPointSize(12)
font.setBold(True)
LabHello.setFont(font)
size=LabHello.sizeHint()
LabHello.setGeometry(70,60,size.width(),size.height())

widgetHello.show()
sys.exit(app.exec())



