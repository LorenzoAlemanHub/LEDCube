class cube
{
  //int cubeSize = 8;
  public:
  led points[8];
  void resetCubePosition()
  {
    /*for (int i = 0; i < cubeSize; i++)
    {

    }*/
    points[0].lev = 0;
    points[0].row = 0;
    points[0].col = 0;

    points[1].lev = 0;
    points[1].row = 0;
    points[1].col = 1;

    points[2].lev = 0;
    points[2].row = 1;
    points[2].col = 0;

    points[3].lev = 0;
    points[3].row = 1;
    points[3].col = 1;

    points[4].lev = 1;
    points[4].row = 0;
    points[4].col = 0;

    points[5].lev = 1;
    points[5].row = 0;
    points[5].col = 1;

    points[6].lev = 1;
    points[6].row = 1;
    points[6].col = 0;

    points[7].lev = 1;
    points[7].row = 1;
    points[7].col = 1;
  }
  /*void setCubeOrigin(int level, int row, int column)
  {
    points
  }*/

  void setCubeColor(byte color[])
  {
    for (auto& l : points)
    {
      l.r = color[0];
      l.g = color[1];
      l.b = color[2];
    }
  }

  void On()
  {
    for (auto& l : points)
    {
      LED(l.lev, l.row, l.col, l.r, l.g, l.b);
    }
  }

  void Off()
  {
    for (auto& l : points)
    {
      LED(l.lev, l.row, l.col, 0, 0, 0);
    }
  }

  void Up()
  {
    Off();
    for (auto& l : points)
    {
      l.lev += 1;
    }
    On();
  }

  void Down()
  {
    Off();
    for (auto& l : points)
    {
      l.lev -= 1;
    }
    On();
  }

  void Left()
  {
    Off();
    for (auto& l : points)
    {
      l.row += 1;
    }
    On();
  }

  void Right()
  {
    Off();
    for (auto& l : points)
    {
      l.row -= 1;
    }
    On();
  }

  void Forward()
  {
    Off();
    for (auto& l : points)
    {
      l.col += 1;
    }
    On();
  }

  void Back()
  {
    Off();
    for (auto& l : points)
    {
      l.col -= 1;
    }
    On();
  }

  void Update()
  {
    Off();
    On();
  }
};