require 'guard'
require 'guard/plugin'
require 'pry'
require 'erb'

module ::Guard
  class Test < ::Guard::Plugin

    def run_all
      Kernel.system("make test")
    end

    def start
      run_all
    end

    def run_on_changes(paths)
      run_paths(paths)
    end

    def run_on_additions(paths)
      run_paths(paths)
    end

    def run_on_modifications(paths)
      run_paths(paths)
    end

    def run_on_removals(paths)
    end

    def run_paths(paths)
      runnable = paths.reduce([]) do |to_run, path|
        if File.exists?(path)
          case
          when File.directory?(path)
            Dir.glob("#{path}/**/*_test.c").each do |path|
              to_run << path
            end
          when File.file?(path)
            to_run << path
          end
        end
        to_run
      end.uniq
      if !runnable.empty?
        main_template = ERB.new(<<-MAIN
<% headers.each do |header| %>
#include "<%= header %>"
<% end %>

int main()
{
  <% tests.each do |test| %>
  <%= test %>
  <% end %>
  return 0;
}
MAIN
)
        headers = runnable.map do |path|
          path.sub('test/', '').chomp(File.extname(path)) + ".h"
        end
        tests = runnable.map do |path|
          File.basename(path, File.extname(path)) + "s();"
        end
        with_test_main(main_template.result(binding)) do |main_filename|
          main_object_file = replace_extension(main_filename, ".o")
          test_objects = runnable.map do |path|
            replace_extension(path, ".o")
          end.join(" ")
          cmd = "make TEST_MAIN=\"#{main_object_file}\" TESTS=\"#{test_objects}\" test_isolated"
          Kernel.system(cmd)
        end
      end
    end

    def replace_extension(filename, new_ext)
      filename.chomp(File.extname(filename)) + new_ext
    end

    def with_test_main(body, &block)
      filename = "out/#{random_string}_test_main.c"
      File.open(filename, 'w') { |file| file.write(body) }
      begin
        block.call(filename)
      ensure
        File.delete(filename)
      end
    end

    def random_string
      (0...8).map { (65 + rand(26)).chr }.join
    end

  end
end

guard 'test' do
  watch(%r{^test/(.+)_test\.c$}) do |match|
    "test/#{match[1]}_test.c"
  end

  watch(%r{^test/(.+)_test\.h$}) do |match|
    "test/#{match[1]}_test.c"
  end

  watch(%r{^src/(.+)\.c$}) do |match|
    "test/#{match[1]}_test.c"
  end

  watch(%r{^include/(.+)\.h$}) do |match|
    "test/#{match[1]}_test.c"
  end

  watch('test/all_test_main.c') do ||
    'test'
  end

  watch('Makefile') do ||
    'test'
  end
end
