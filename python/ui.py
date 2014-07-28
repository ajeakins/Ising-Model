
import sys
sys.path.append( "/data/dev/ising_model/build/bind" )

from ising_model import MetropolisHastings, Initialise

from PyQt4 import QtGui, QtCore

class IsingModelDialog( QtGui.QMainWindow ):

	def __init__( self, parent = None ):
		QtGui.QMainWindow.__init__( self, parent )

		self.__sim = MetropolisHastings( 100, Initialise.kRandom )

		self.__createWidgets()
		self.__updateImage()

	def __createWidgets( self ):

		self.__label = QtGui.QLabel()
		run_button = QtGui.QPushButton( "Run" )
		run_button.released.connect( self.__run )

		teperature = QtGui.QLineEdit()
		teperature.textChanged.connect( self.__setTemperature )
		teperature.setText( "0" )

		layout = QtGui.QVBoxLayout()
		widget = QtGui.QWidget()
		widget.setLayout( layout )

		layout.addWidget( self.__label )
		layout.addWidget( teperature )
		layout.addWidget( run_button )

		self.setCentralWidget( widget )

	def __setTemperature( self, tempature ):
		try:
			tempature = int( tempature )
		except Exception:
			pass
		else:
			self.__sim.setTemperature( tempature )

	def __updateImage( self ):

		image = QtGui.QImage(
					self.__sim.size(),
					self.__sim.size(),
					QtGui.QImage.Format_Mono
					)

		for x in xrange( 0, self.__sim.size() ):
			for y in xrange( 0, self.__sim.size() ):
				if self.__sim.spin( x, y ) > 0:
					image.setPixel( x,y, 1 )
				else:
					image.setPixel( x, y, 0 )

		scale = 400
		self.__label.setPixmap( QtGui.QPixmap.fromImage( image ).scaled( scale, scale ) )

	def __run( self ):
		self.__sim.run( 1 )
		self.__updateImage()

def main():
	app = QtGui.QApplication([])
	dialog = IsingModelDialog()
	dialog.show()
	app.exec_()

if __name__ == "__main__":
	main()