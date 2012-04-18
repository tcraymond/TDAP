#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
//Can't do this because it collides with Matrix from the FE stuff!
//using namespace System::Drawing::Drawing2D;

namespace TDAP {

	/// <summary>
	/// Summary for frmContourPlot
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class frmContourPlot : public System::Windows::Forms::Form
	{
	public:
		List<PointF>^ lines;
		List<RectangleF>^ rectangles;
		double xmin;
		double xmax;
		double ymin;
		double ymax;

		frmContourPlot(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			lines = gcnew List<PointF>;
			rectangles = gcnew List<RectangleF>;
		}

		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmContourPlot()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// frmContourPlot
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 264);
			this->Name = L"frmContourPlot";
			this->Text = L"frmContourPlot";
			this->Resize += gcnew System::EventHandler(this, &frmContourPlot::frmContourPlot_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion

	public: 
		System::Void setPhysicalSize(double xmin_in, double xmax_in, double ymin_in, double ymax_in){
			xmin = xmin_in;
			xmax = xmax_in;
			ymin = ymin_in;
			ymax = ymax_in;
		}
		
		System::Void drawPlot(){
			Graphics^ plotGraph = this->CreateGraphics();
			plotGraph->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
			plotGraph->Clear(Color::White);
			Pen^ plotPen = gcnew Pen(Color::Black,0);
			Color customColor = Color::FromArgb( 50, Color::Gray );
			SolidBrush^ wdgBrush = gcnew SolidBrush( customColor );
			Pen^ wdgPen = gcnew Pen(wdgBrush);

			double scale = this->ClientRectangle.Height / (ymax - ymin);
			if((this->ClientRectangle.Width / (xmax-xmin)) < scale) {
				scale = this->ClientRectangle.Width / (xmax-xmin);
			}
			plotGraph->RotateTransform(180);
			plotGraph->ScaleTransform(-scale, scale);
			plotGraph->TranslateTransform(0, this->ClientRectangle.Height, Drawing2D::MatrixOrder::Append);
			//RectangleF world_rect = RectangleF(xmin, ymax, xmax-xmin, ymin-ymax);
			//array<PointF>^ client_points = {PointF(plotForm->ClientRectangle.Left, plotForm->ClientRectangle.Bottom), PointF(plotForm->ClientRectangle.Right, plotForm->ClientRectangle.Bottom), PointF(plotForm->ClientRectangle.Left, plotForm->ClientRectangle.Top)};
			//plotGraph->Transform = gcnew Matrix(world_rect, client_points);

			for (int i=0;i<lines->Count;i=i+2){
				plotGraph->DrawLine(plotPen, lines[i], lines[i+1]);
			}
			for (int i=0;i<rectangles->Count;i++){
				plotGraph->FillRectangle(wdgBrush, rectangles[i].X, rectangles[i].Y, rectangles[i].Width, rectangles[i].Height);
			}
				
		}

	private: System::Void frmContourPlot_Resize(System::Object^  sender, System::EventArgs^  e) {
				 drawPlot();
			 }
	};
}
