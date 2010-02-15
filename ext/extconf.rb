# extconf.rb for ruby-iup extension module.
#
# Copyright (C) 2008 Park Heesob <phasis@gmail.com>
#
# This program is distributed under the terms of the MIT license.
# See the included COPYRIGHT file for the terms of this license.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
require 'mkmf' 

if RUBY_PLATFORM =~ /mingw32/
  dir_config('iup','./iup-mingw32/include','./iup-mingw32')
elsif RUBY_PLATFORM =~ /mswin32/
  dir_config('iup','./iup-mswin32/include','./iup-mswin32')
else
  dir_config('iup','./iup-linux/include','./iup-linux')
  have_library('GL')
end

have_library('freetype6')
have_library('freetype')
have_library('stdc++')
have_library('gdi32')
have_library('comctl32')
have_library('comdlg32')
have_library('opengl32')
have_library('ole32')
have_library('oleaut32')
have_library('uuid')
have_library('iup')
have_library('pdflib')
have_library('cdgdk')
have_library('cdpdf')
have_library('cdcontextplus')
have_library('cd')
have_library('im')
have_library('im_avi')
have_library('im_fftw')
have_library('im_jp2')
have_library('im_process')
have_library('iup_pplot')
have_library('iupcd')
have_library('iupole')
have_library('iupcontrols')
have_library('iupgl')
have_library('iupim')
have_library('iupimglib')


if RUBY_PLATFORM =~ /mswin32/
  $LOCAL_LIBS = "-link /nodefaultlib:msvcrt.lib"
elsif RUBY_PLATFORM =~ /linux/
  $LOCAL_LIBS = `pkg-config --libs gtk+-2.0`
end

create_makefile('iup')
