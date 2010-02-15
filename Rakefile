require 'rake'
require 'rake/clean'
require 'rake/testtask'
require 'rbconfig'
include Config

make = CONFIG['host_os'] =~ /mswin/i ? 'nmake' : 'make'

desc 'Build the ruby.exe.manifest if it does not already exist'
task :build_manifest do
  version = CONFIG['host_os'].split('_')[1]
   
  if version && version.to_i >= 80
    unless File.exist?(File.join(CONFIG['bindir'], 'ruby.exe.manifest'))
      Dir.chdir(CONFIG['bindir']) do
        sh "mt -inputresource:ruby.exe;2 -out:ruby.exe.manifest"
      end
    end
  end
end

desc 'Install the ruby-iup library (non-gem)'
task :install => [:build] do
  Dir.chdir('ext'){
    sh "#{make} install"
  }
end

desc 'Clean any build files for ruby-iup'
task :clean do
  Dir.chdir('ext') do
    if File.exists?('iup.so') || File.exists?('Makefile')
    then
      sh "#{make} distclean"
    end
  end

  # Cleanup any files generated by the build_binary_gem task
  rm_rf('lib') if File.exists?('lib')
  Dir["*.gem"].each{ |f| File.delete(f) }
end

desc "Build ruby-iup (but don't install it)"
task :build => [:clean, :build_manifest] do
  Dir.chdir('ext') do
    ruby "extconf.rb"
    sh make
  end
end

namespace 'gem' do
  desc 'Build a standard gem'
  task :create => [:clean] do 
    spec = eval(IO.read('ruby-iup.gemspec'))
    Gem::Builder.new(spec).build
  end

  desc 'Build a binary gem'
  task :binary => [:build] do
    mkdir_p 'lib'
    cp 'ext/iup.so', 'lib'

    spec = eval(IO.read('ruby-iup.gemspec'))
    spec.platform = Gem::Platform::CURRENT
    spec.extensions = nil
    spec.files = spec.files.reject{ |f| f.include?('ext') }

    Gem::Builder.new(spec).build
  end

  desc 'Install the gem'
  task :install => [:create] do
    file = Dir["*.gem"].first
    sh "gem install #{file}"
  end
end

namespace 'test' do
  Rake::TestTask.new(:all) do |test|
    task :all => [:build]
    test.libs << 'ext'
    test.warning = true
    test.verbose = true
  end
end
