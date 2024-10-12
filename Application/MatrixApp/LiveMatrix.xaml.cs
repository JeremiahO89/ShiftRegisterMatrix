using Microsoft.Maui.Controls;
using Microsoft.UI.Xaml.Input;
using System;
using System.Collections.Generic;

namespace MatrixApp;

public partial class LiveMatrix : ContentPage
{
    public LiveMatrix()
    {
        InitializeComponent();
        CreateDotMatrix();
    }

    // Set Rows and Columns
    private int Rows = 0;
    private int Columns = 0;

    // Handle the change in the picker
    private void OnPickerIndexChanged(object sender, EventArgs e)
    {
        // Show or hide custom matrix layout based on selection
        if (matrixPicker.SelectedItem?.ToString() == "Custom")
        {
            customMatrixLayout.IsVisible = true;
        }
        else
        {
            customMatrixLayout.IsVisible = false;
        }

        string inputWord = matrixPicker.SelectedItem?.ToString().Trim();
        string[] numList = inputWord.ToLower().Split('x');
        if (numList.Length >= 2)
        {
            Rows = Convert.ToInt32(numList[0]);
            Columns = Convert.ToInt32(numList[1]);

            // Update the matrix because of input change
            CreateDotMatrix();
        }
    }

    private const double DotSize = 30;
    private const double baseDotSize = DotSize + 5;
    private List<BoxView> _dots = new List<BoxView>();

    private void CreateDotMatrix()
    {
        // Clear existing rows and columns in the grid before creating new ones
        DotGrid.RowDefinitions.Clear();
        DotGrid.ColumnDefinitions.Clear();
        DotGrid.Children.Clear();
        _dots.Clear(); // Clear the dots list

        // Set the row and column definitions based on Rows and Columns
        for (int i = 0; i < Rows; i++)
        {
            DotGrid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(baseDotSize + 2) });
        }
        for (int j = 0; j < Columns; j++)
        {
            DotGrid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(baseDotSize + 2) });
        }

        // Create dots and add them to the grid
        for (int row = 0; row < Rows; row++)
        {
            for (int col = 0; col < Columns; col++)
            {
                var dot = new BoxView
                {
                    WidthRequest = DotSize,
                    HeightRequest = DotSize,
                    BackgroundColor = Colors.Transparent, // Inner fill is transparent
                    Margin = new Thickness(5),
                    CornerRadius = (float)(DotSize / 2),  // Make it circular
                };

                var baseDot = new BoxView
                {
                    WidthRequest = baseDotSize,
                    HeightRequest = baseDotSize,
                    BackgroundColor = Colors.LightGrey,
                    Margin = new Thickness(5),
                    CornerRadius = (float)(baseDotSize / 2),  // Make it circular
                    Opacity = 0.25
                };

                // Add gesture recognizers for dot selection
                dot.GestureRecognizers.Add(new TapGestureRecognizer
                {
                    Command = new Command(() => ToggleDot(dot)),
                });

                // Create and add PanGestureRecognizer
                var panGesture = new PanGestureRecognizer
                {
                    TouchPoints = 1
                };
                panGesture.PanUpdated += (s, e) =>
                {
                    if (e.StatusType == GestureStatus.Running)
                    {
                        ToggleDot(dot);
                    }
                };

                // Add the PanGestureRecognizer to the dot
                dot.GestureRecognizers.Add(panGesture);

                // Add the dot and baseDot to the grid's children collection
                DotGrid.Children.Add(baseDot);
                Grid.SetRow(baseDot, row);
                Grid.SetColumn(baseDot, col);

                DotGrid.Children.Add(dot);
                Grid.SetRow(dot, row);
                Grid.SetColumn(dot, col);

                _dots.Add(dot);
            }
        }
        UpdateDotStatusLabel(); // Update the label whenever the matrix is created
    }

    private void ToggleDot(BoxView dot)
    {
        // Toggle the dot's color between filled and transparent
        if (dot.BackgroundColor == Colors.Transparent)
        {
            dot.BackgroundColor = Colors.Blue; // Change to filled color
        }
        else
        {
            dot.BackgroundColor = Colors.Transparent; // Change to empty color
        }

        UpdateDotStatusLabel(); // Update the label whenever a dot is toggled
    }

    private void UpdateDotStatusLabel()
    {
        // Create a string representation of the dot states
        var status = "";

        for (int row = 0; row < Rows; row++)
        {
            for (int col = 0; col < Columns; col++)
            {
                var dot = _dots[row * Columns + col];
                status += dot.BackgroundColor == Colors.Blue ? "1 " : "0 ";
            }
            status += "\n"; // New line for each row
        }

        DotStatusLabel.Text = status.Trim(); // Update the label text
    }
}
