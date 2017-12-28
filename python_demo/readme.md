
1.  from PIL import Image
2.  import face_recognition
3,  img_path = raw_input("image path:")
4.  image = face_recognition.load_image_file(img_path)
5.  face_locations = face_recognition.face_locations(image)
6.  print("Found {} face(s) in this photograph.".format(len(face_locations)))
第1、2行导入PIL库中的Image模块和face_recognition库。第3行，等待用户输入头像图片的路径。第4行，把路径所指的图像数据读入image中。第5行，调用face_locations处理image中的图像数据，对图片中的人脸进行识别定位，定位后的得到的像素坐标数据放在face_locations里。第6行在shell里输出图片里识别到的人脸的个数。

7.  human_img = Image.open(img_path)
8.  human_img = human_img.convert("RGBA")
9.  hat_img = Image.open("./hat.png")
10. hat_img = hat_img.convert("RGBA")
第7、8行，把路径所指的图像数据读入human_img中，并转换为四通道RGBA模式。9、10行读入帽子图像并做相同处理。

11. for face_location in face_locations:
12.     top, right, bottom, left = face_location
13.     top -= 10
14.     print("A face is located at pixel location Top: {}, Left: {}, Bottom: {}, Right: {}".format(top, left, bottom, right))
   
15.     head_h = bottom-top#hight of head
16.     head_l = right-left#length of head
    
17.     hat_img = hat_img.resize( (head_l,head_h) )#convert size of hat
18.     hat_region = hat_img

19.     human_region = ( left, top-head_h, right, top )

20.     human_img.paste(hat_region, human_region,mask=hat_img)
    
21. human_img.show()
如果一张图里有多张人脸，face_recognition.face_locations(image)会返回每张人脸的位置信息，存放在一个list里。因此第11行是遍历face_locations里的每张人脸的数据。第12行解包一个人脸像素坐标数据，得到top，right，bottom，left分别为示意图中的y1，x2，y2，x1。第13行，为啥y1要减10个像素？因为人脸识别得到的y1最多到你额头的位置，所以再把这个坐标往上提一提帽子才戴得更自然。第14行输出坐标数据方便调试。第15、16行计算人脸的高度和宽度。第17行使用resize()根据人脸的大小调整帽子的大小，因为图像中的人脸有大有小，调整后看起来更和谐。第18行，将帽子图像作为顶部图层图像。第19行，确定底部图层（头像图片）被覆盖的区域（就是帽子放置区域）。第20行，把顶部图层与底部图层拼接（不太明白的看下图）。然后一个循环结束，亦即完成图片中一个人的戴帽操作，接着进行下个人的戴帽，直到所有人都戴上了帽子。最后21行，完成输出。
