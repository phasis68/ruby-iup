require 'rubygems'

Gem::Specification.new do |spec|
  spec.name       = 'ruby-iup'
  spec.version    = '0.1.0'
  spec.authors    = ['Park Heesob']
  spec.email      = 'phasis@gmail.com'
  spec.homepage   = 'http://rubyforge.org/projects/ruby-iup'
  spec.platform   = Gem::Platform::RUBY
  spec.summary    = 'An interface to the IUP GUI toolkit'
  spec.has_rdoc   = true
  spec.test_files = Dir['test/test*']
  spec.extensions = ['ext/extconf.rb']
  spec.files      = Dir['**/*'].reject{ |f| f.include?('git')||f.include?('CVS') }
   
  spec.rubyforge_project = 'ruby-iup'
  spec.required_ruby_version = '>= 1.8.2'
  spec.extra_rdoc_files = ['README', 'CHANGES', 'MANIFEST']
   
  spec.add_development_dependency('test-unit', '>= 2.0.6')
   
  spec.description = <<-EOF
    ruby-iup is an extension module for Ruby that provides an interface to the IUP GUI 
    toolkit. IUP is a portable toolkit for building graphical user interfaces.
  EOF
end
