############################################################################
# test_ruby_iup.rb
# 
# Test case for the Iup class. You should run this as Rake task,
# i.e. 'rake test', instead of running it directly.
############################################################################
require 'rubygems'
gem 'test-unit'

require 'iup'
require 'test/unit'
include Iup

class TC_RUBY_IUP < Test::Unit::TestCase
   def setup
   end

   def test_version
      assert_equal('0.1.0', RUBY_IUP_VERSION)
   end


   def teardown
   end
end
