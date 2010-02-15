require 'rubygems'
require 'iup'
require 'opengl'

include Gl

redraw = lambda do |ih,x,y|
  size = ih.rastersize
  w,h = size.scan(/\d+/).map{|x|x.to_i}

  Iup.GLMakeCurrent(ih)
  glViewport(0, 0, w, h)
  
  glMatrixMode(GL_PROJECTION)
  glLoadIdentity()
  glOrtho(0, 1, 1, 0, -1.0, 1.0)
  glMatrixMode(GL_MODELVIEW)
  glLoadIdentity()
  glPushMatrix()
  glTranslate(0.25,0.5, 0)
  glScale(0.2, 0.2, 1)

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

  glClearColor(0,0,0,1)
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT)
  glEnable(GL_BLEND)

  # draw rectangle
  glColor(1, 1, 0, 0.8)
  glRect(-1,-1,1,1) 
  
  # Create List That Draws the Circle
  planet = glGenLists(1) 
  orbit = glGenLists(2) 

  glNewList(planet, GL_COMPILE)
    glBegin(GL_POLYGON)
      for i in 0..100
        cosine = Math.cos(i * 2 * Math::PI/100.0)
        sine   = Math.sin(i * 2 * Math::PI/100.0)
        glVertex(cosine,sine)
      end
    glEnd()
  glEndList()

  glNewList(orbit, GL_COMPILE)
    glBegin(GL_LINE_LOOP)
      for i in 0..100
        cosine = Math.cos(i * 2 * Math::PI/100.0)
        sine   = Math.sin(i * 2 * Math::PI/100.0)
        glVertex(cosine, sine)
      end
    glEnd()
  glEndList()

  glColor( 0, 0.5, 0, 0.8)
  glCallList(planet)

  glColor( 0, 0, 0, 1 )
  glCallList(orbit)

  glEnableClientState(GL_VERTEX_ARRAY)
  
  vertices  = [[-3**(0.5)/2, 1.0/2], [3**(0.5)/2, 0.5], [0.0, -1.0], [-3**(0.5)/2, -1.0/2], [3**(0.5)/2, -1.0/2], [0.0, 1.0] ]
    
  glVertexPointer(2,GL_FLOAT,0,vertices.flatten.pack("f*"))
  
  # draw first triangle
  glColor( 0, 0, 1, 0.5 )

  glBegin(GL_TRIANGLES)
    glArrayElement(0)
    glArrayElement(1)
    glArrayElement(2)
  glEnd()

  # draw second triangle
  glColor( 1, 0, 0, 0.5 )
  glVertexPointer(2,GL_FLOAT,0,vertices.flatten.pack("f*"))
  glDrawArrays(GL_TRIANGLES, 3, 3)

  # draw triangles outline
  glColor(1,1,1,1)
  elements = [ 0, 1, 2].pack("I*")
  glDrawElements(GL_LINE_LOOP,3,GL_UNSIGNED_INT,elements)
  elements = [ 3, 4, 5].pack("I*")   
  glDrawElements(GL_LINE_LOOP,3,GL_UNSIGNED_INT,elements)

  glDisableClientState(GL_VERTEX_ARRAY)

  glPopMatrix()
  glTranslate(0.75,0.5, 0)
  glScale(0.2, 0.2, 1)

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

  # draw rectangle
  glColor( 1, 1, 0, 0.8 )
  
  glBegin(GL_QUADS)
    glVertex(-1,-1)
    glVertex( 1,-1)
    glVertex( 1, 1)
    glVertex(-1, 1)
  glEnd()
  
  glColor( 0, 0.5, 0, 0.8 )
  glBegin(GL_POLYGON)
    for i in 0..100 
      cosine = Math.cos(i * 2.0 * Math::PI/100.0)
      sine   = Math.sin(i * 2.0 * Math::PI/100.0)
      glVertex(cosine,sine)
    end
  glEnd()

  glColor( 0, 0, 0, 1 )
  glBegin(GL_LINE_LOOP)
    for i in 0..100
      cosine = Math.cos(i * 2.0 * Math::PI/100.0)
      sine   = Math.sin(i * 2.0 * Math::PI/100.0)
      glVertex(cosine, sine)
    end
  glEnd()

  # draw first triangle
  glColor( 0, 0, 1, 0.5 )
  glBegin(GL_TRIANGLES)
    glVertex(*vertices[0])
    glVertex(*vertices[1])
    glVertex(*vertices[2])
  glEnd()
  # draw second triangle
  glColor( 1, 0, 0, 0.5 )
  glBegin(GL_TRIANGLES)
    glVertex(*vertices[3])
    glVertex(*vertices[4])
    glVertex(*vertices[5])
  glEnd()
  # draw triangles outline
  glColor(1,1,1,1)
  glBegin(GL_LINE_LOOP)
    glVertex(*vertices[0])
    glVertex(*vertices[1])
    glVertex(*vertices[2])
  glEnd()
  glBegin(GL_LINE_LOOP)
    glVertex(*vertices[3])
    glVertex(*vertices[4])
    glVertex(*vertices[5])
  glEnd()
    
  Iup.GLSwapBuffers(ih) 

  Iup::DEFAULT
end


  canvas = Iup.GLCanvas()
  canvas.action = redraw
  canvas.buffer = "DOUBLE"
  canvas.rastersize = "123x200"

  finale = Iup.Hbox([Iup.Fill(), 
                   canvas, 
                   Iup.Fill()])

  dg = Iup.Dialog(finale,:title=>"IupGLCanvas")

  dg.Show()
  Iup.MainLoop
  dg.Destroy()
