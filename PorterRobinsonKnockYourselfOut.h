void expandingCube(int d)
{
  int col = 0;
  int min, max, b1, b2;
  bool light = false;
  for (int i = 3; i >= 0; i--) // 4 cubes, 2,4,6,8 cubed
  {
    min = 0 + i;
    max = 7 - i;
    // Light LED when it is along one of the 3 axis within the bounds
    // x: (col == min || col == max) && (row >= min && row <= max)
    // y: (row == min || row == max) && (col >= min && col <= max)
    // z: (lev == min || lev == max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,15,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,15,0,0);
              }
        }
      }
    }
    delay(d);
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,0,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,0,0,0);
              }
        }
      }
    }
  }
}

void contractingCube(int d)
{
  int col = 0;
  int min, max, b1, b2;
  bool light = false;
  for (int i = 0; i <= 3; i++) // 4 cubes, 2,4,6,8 cubed
  {
    min = 0 + i;
    max = 7 - i;
    // Light LED when it is along one of the 3 axis within the bounds
    // x: (col == min || col == max) && (row >= min && row <= max)
    // y: (row == min || row == max) && (col >= min && col <= max)
    // z: (lev == min || lev == max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,15,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,15,0,0);
              }
        }
      }
    }
    delay(d);
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,0,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,0,0,0);
              }
        }
      }
    }
  }
}

void expandingSquare(int col)
{
  //int col = 0;
  int lowerBound, upperBound, b1, b2;
  bool light = false;
  for (int i = 3; i >= 0; i--) // 4 cubes, 2,4,6,8 cubed
  {
    lowerBound = 0 + i;
    upperBound = 7 - i;
    // Light LED:
    // if lev == bound, light inbetween bound
    // else, light only at bounds
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        if (lev == lowerBound || lev == upperBound)
        {
          // light between
          if (row >= lowerBound && row <= upperBound)
          {
            LED(lev,row,col,15,0,0);
          }
        }
        else if (lev > lowerBound && lev < upperBound)
        {
          if ((row == lowerBound || row == upperBound))
          {
            LED(lev,row,col,15,0,0);
          }
        }
      }
    }
    delay(100);
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        if (lev == lowerBound || lev == upperBound)
        {
          // light between
          if (row >= lowerBound && row <= upperBound)
          {
            LED(lev,row,col,0,0,0);
          }
        }
        else if (lev > lowerBound && lev < upperBound)
        {
          if ((row == lowerBound || row == upperBound))
          {
            LED(lev,row,col,0,0,0);
          }
        }
      }
    }
  }
}