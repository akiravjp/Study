// ParseKindleNotes project main.go
package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"regexp"
	"strings"
)

func ReadLine(fileName string, handler func(string)) error {
	f, err := os.Open(fileName)
	if err != nil {
		return err
	}
	buf := bufio.NewReader(f)
	for {
		line, err := buf.ReadString('\n')
		line = strings.TrimSpace(line)
		handler(line)
		if err != nil {
			if err == io.EOF {
				return nil
			}
			return err
		}
	}
	return nil
}

func main() {

	r, _ := regexp.Compile("p([a-z]+)ch")
	fmt.Println(r)

	ReadLine("Kindle-Notebook.csv", ParseWord)
}

func ParseWord(line string) {
	strs := strings.Split(line, ",")

	if len(strs) >= 4 {
		// ����һ��Trim ��ɾ�� s ��β�����İ����� cutset �е��ַ�
		//		word := strings.Trim(strs[3], " \".����:")
		// ��������ʹ��������ʽ�ҵ���
		// eg: summer-cloud, it's
		wordTrimSpace := strings.TrimSpace(strs[3])
		reg := regexp.MustCompile(`[- A-Za-z\']+`)
		word := reg.FindString(wordTrimSpace)
		// construct
		newLine := "|" + word + "|"
		fmt.Println(newLine)
	}
}
