package pro.emakei.luado

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.KeyEvent
import android.view.View
import pro.emakei.luado.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        binding.btnRun.setOnClickListener {

            val inputText = binding.inputText.text.toString()
            var text = binding.sampleText.text.toString()
            text += "\n\n"
            text += evaluateExpression(inputText)
            binding.sampleText.text = text
            binding.inputText.text.clear()

        }
    }

    override fun onDestroy() {
        super.onDestroy()

        freeMemory()

    }

    /**
     * A native method that is implemented by the 'luado' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun evaluateExpression(exp: String): String

    external fun freeMemory()

    companion object {
        // Used to load the 'luado' library on application startup.
        init {
            System.loadLibrary("luado")
        }
    }
}
