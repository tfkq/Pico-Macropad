/**
 * @file layer.h
 * @author zauberwild
 * @brief layer class, which saves the all the colors, macros, everything
 * @version 0.1
 * @date 2022-04-04
 *
 * @copyright MIT license, Arvid Randow, 2022
 *
 */

// #ifndef layer_h
// #define layer_h
// namespace Layer
// {

// 	int begin();

// 	void update();

// 	void set_layer(int n);
// 	bool get_input_since_change();
// }

// int Layer::begin()
// {
// 	Serial.println("### READING CONFIG ###");

// 	if (!LittleFS.begin())
// 	{
// 		Serial.println("[ERROR] couldn't mount filesystem");
// 		return 1;
// 	}

// 	LittleFS.end();
// }

// #endif